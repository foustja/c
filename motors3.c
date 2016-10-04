/* motors3.c*/

#include <unistd.h>
#include <dmotor.h>

int main(int argc, char **argv)
{
  /* start the motor */
  cls();
  cputs("speed");
  msleep(500);
  cputs("150");

  motor_a_dir(fwd);
  motor_c_dir(fwd);
  motor_a_speed(150);
  motor_c_speed(150);

  msleep(2000);
  cls();
  motor_a_dir(off);
  motor_c_dir(off);

  msleep(2000);

  cputs("speed");
  msleep(500);
  cputs("100");

  motor_a_dir(fwd);
  motor_c_dir(fwd);
  motor_a_speed(100-l

  motor_c_speed(100);

  msleep(2000);
  cls();
  motor_a_dir(off);
  motor_c_dir(off);

  cputs("speed");
  msleep(500);
  cputs("75");


  msleep(2000);

  motor_a_dir(fwd);
  motor_c_dir(fwd);
  motor_a_speed(75);
  motor_c_speed(75);

  return 0;
}
