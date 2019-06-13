#include "DS18x20.h"

  DS18x20::DS18x20(uint8_t pin, Milliseconds timeInterval)
  : ds(OneWire(pin)),
    updateInterval(timeInterval),
    lastUpdatedTime(0),
    state(DS18x20SensorState_Waiting),
    forceUpdateRequested(false) {}

    void DS18x20::SetUpdateInterval (Milliseconds interval)
    {
      updateInterval = interval;
    }

    void DS18x20::ForceUpdate ()
    {
      forceUpdateRequested = true;
    }

   void DS18x20::Update (Milliseconds currentTime)
   {
     if (state == DS18x20SensorState_Waiting
         && (abs(currentTime - lastUpdatedTime) >= updateInterval || forceUpdateRequested))
     {
       forceUpdateRequested = false;
       lastUpdatedTime = currentTime;
       
       Prepare();
     }
     else if (state == DS18x20SensorState_PrepareComplete
              && abs(currentTime - lastUpdatedTime) >= SEC_IN_MILLIS)
     {
       Proccess();
     }
   }

   void  DS18x20::Prepare ()
   {
       if ( !ds.search(addr))
       {
         ds.reset_search();
         return;
       }

       if (OneWire::crc8(addr, 7) != addr[7])
       {
           return;
       }

       switch (addr[0])
       {
         case 0x10:
           type_s = 1;
           break;
         case 0x28:
           type_s = 0;
           break;
         case 0x22:
           type_s = 0;
           break;
         default:
           return;
       }

       ds.reset();
       ds.select(addr);
       ds.write(0x44, 1);
       state = DS18x20SensorState_PrepareComplete;
     }

   void  DS18x20::Proccess ()
   {
       ds.reset();
       ds.select(addr);
       ds.write(0xBE);

       for ( i = 0; i < 9; i++)
       {
         data[i] = ds.read();
       }

       int16_t raw = (data[1] << 8) | data[0];

       if (type_s)
       {
         raw = raw << 3;

         if (data[7] == 0x10)
         {
           raw = (raw & 0xFFF0) + 12 - data[6];
         }
       }
       else
       {
         byte cfg = (data[4] & 0x60);
         if (cfg == 0x00) raw = raw & ~7;
         else if (cfg == 0x20) raw = raw & ~3;
         else if (cfg == 0x40) raw = raw & ~1;
       }

       float potentialCelcius = (float)raw / 16.0;

       if (potentialCelcius != celsius)
       {
           celsius = potentialCelcius;
           fahrenheit = celsius * 1.8 + 32.0;

           UpdateTemperature(celsius);
       }

       state = DS18x20SensorState_Waiting;
     }
