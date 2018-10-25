#define PERIOD_10ms 0x01
#define PERIOD_14ms 0x02
#define PERIOD_19ms 0x03

void Timer_ISR(void)
{
   static char State = PERIOD_10ms;

   switch(State)
   {
      case PERIOD_10ms:
      {
         // Toggle pin;
         // Timer Stop;
         // Change period to 14ms;
         // Timer Start;
         break;
      }
      case PERIOD_14ms:
      {
         // Toggle pin;
         // Timer Stop;
         // Change period to 19ms;
         // Timer Start;
         break;
      }
      case PERIOD_19ms:
      {
         // Toggle pin;
         // Timer Stop;
         // Change period to 10ms;
         // Timer Start;
         break;
      }
      default:
      {
         /* Timer_ISR entered undefined state */
         // Make default period 10ms
         break;
      }
   }
}
