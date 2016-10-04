// message1.c
//Jack Foust
//foustja@gmail.com
//05.06.2016
//C program for RCX 2.0 using brickOS
//RCX emits a light signal, sensor detects reflected signal
//and backs up, turns in response. Based on a similar program
//by Mark Overmars in NQC.

#include <unistd.h>
#include <conio.h>
#include <dmotor.h>
#include <dsensor.h>
#include <string.h>
#include <lnp.h>
#include <lnp-logical.h>
#include <tm.h>
#include <sys/battery.h>
#include <dsound.h>

#define LIGHT_THRESHOLD 0x200
#define BACKUP_TIME 2000
#define TURN_TIME 1000
#define FWD_TIME 1000
#define SHORT_DELAY 100
#define LONG_DELAY 1000
#define SOUND_DUR 20

tid_t thread1;
tid_t thread2;

int battery_level;

static const note_t notes[ ] =
 {
   {PITCH_A5, EIGHTH}, {PITCH_C5, EIGHTH}, {PITCH_D5, EIGHTH},
   {PITCH_E5, EIGHTH}, {PITCH_G5, EIGHTH}, {PITCH_END, 0}
 };

int display_sensor();
int emit_signal();
int respond_signal();
int music();


int main(int argc, char **argv)
{
  battery_level = get_battery_mv();

  dsound_system(DSOUND_BEEP);

  cls();
  cputs("BATT");
  msleep(LONG_DELAY);

  dsound_system(DSOUND_BEEP);

  cls();
  lcd_int(battery_level);
  msleep(LONG_DELAY);

  dsound_system(DSOUND_BEEP);

  cls();
  cputs("START");
  msleep(LONG_DELAY);

  dsound_system(DSOUND_BEEP);
  msleep(LONG_DELAY);
  dsound_system(DSOUND_BEEP);

  motor_a_dir(fwd); //start forward movement
  motor_c_dir(fwd);
  motor_a_speed(MAX_SPEED);
  motor_c_speed(MAX_SPEED);

  thread1 = execi(&emit_signal, 0, 0, PRIO_NORMAL, DEFAULT_STACK_SIZE);
  thread2 = execi(&respond_signal, 0, 0, PRIO_NORMAL, DEFAULT_STACK_SIZE);

  while(!shutdown_requested())
  {
    msleep(SHORT_DELAY);
  }

  killall(PRIO_NORMAL);

  return 0;
}


int emit_signal()  //loop emits 1 byte signal every 100 ms
{                   //using lnp_integrity_write()
  char *msg="X";

  while(1)
  {
    lnp_integrity_write(msg, 1);
    msleep(SHORT_DELAY);
  }

  return 0;
}


int respond_signal()  //detects and moves in response to reflected signal
{
  int last_level;

  ds_active(&SENSOR_1);

  while(1)
  {
  lcd_int(LIGHT_1);
  last_level = SENSOR_1;
  msleep(SHORT_DELAY);

  if(SENSOR_1 < last_level - LIGHT_THRESHOLD)
    {
      music();
      //lcd_int(LIGHT_1);
      cputs("REV");
      motor_a_dir(rev);
      motor_c_dir(rev);
      msleep(BACKUP_TIME);

      cputs("TURN");
      motor_a_dir(fwd);
      motor_c_dir(rev);
      msleep(TURN_TIME);

      cputs("FWD");
      motor_a_dir(fwd);
      motor_c_dir(fwd);
      msleep(FWD_TIME);
    }
  }

  return 0;
}

int music()
{
  dsound_set_duration(SOUND_DUR);
  dsound_play(notes);
  wait_event(dsound_finished, 0);

  return 0;
}
