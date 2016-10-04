/* motors2.c */

#include <unistd.h>
#include <dmotor.h>

int main(int argc, char **argv)
{

  int k;

  /* start the motor */
  motor_a_dir(fwd);
  motor_c_dir(fwd);
  motor_a_speed(MAX_SPEED);
  motor_c_speed(MAX_SPEED);

  /* slow down the motor gradually */
  for (k=MAX_SPEED; k>=0; k--)
    {
      /* slow the motor down a notch */
      motor_a_speed(k);
      motor_c_speed(k);

      /*this function makes the robot wait for 20 milliseconds. */
      msleep(20);
    }

  motor_a_dir(off);
  motor_c_dir(off);
  return 0;
}
