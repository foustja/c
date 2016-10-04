/* motors1.c */

#include <unistd.h>
#include <dmotor.h>

int main(int argc, char **argv)
{
  /* start the motor */
  motor_a_dir(fwd);
  motor_c_dir(fwd);
  motor_a_speed(100);
  motor_c_speed(100);
}
