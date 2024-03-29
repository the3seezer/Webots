/*
 * File:          four_wheeled_collision_avoidance.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/motor.h>, etc.
 */
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>

/*
 * You may want to add macros here.
 */
#define TIME_STEP 64

/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv) {
  /* necessary to initialize webots stuff */
  wb_robot_init();

  /*
   * You should declare here WbDeviceTag variables for storing
   * robot devices like this:
   *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
   *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
   */
  int i = 0;
  bool avoid_obstacle_counter = 0;
  
  char ds_names[ 2 ][ 10 ] = { 
    "ds_right", "ds_left"
  }; 
  WbDeviceTag ds[ 2 ];
  for ( i = 0; i < 2; i++ ) { 
    ds[ i ] = wb_robot_get_device( ds_names[ i ] );
    wb_distance_sensor_enable( ds[ i ], TIME_STEP );
  } // end for
  
  char wheel_names[ 4 ][ 7 ] = { 
    "wheel1", "wheel2", "wheel3", "wheel4"
  };
  WbDeviceTag wheel[ 4 ];
  for ( i = 0; i < 4; i++ ) { 
    wheel[ i ] = wb_robot_get_device( wheel_names[ i ] );
    wb_motor_set_position( wheel[ i ], INFINITY );
  } // end for

  /* main loop
   * Perform simulation steps of TIME_STEP milliseconds
   * and leave the loop when the simulation is over
   */
  while (wb_robot_step(TIME_STEP) != -1) {
    /*
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     Process sensor data here
     */
  double right_speed = 1.0;
  double left_speed = 1.0;
  
  if ( avoid_obstacle_counter > 0 ) { 
    avoid_obstacle_counter--;
    right_speed = -1.0;
    left_speed = 1.0;
  } // end if
  else { 
    double ds_values[ 2 ];
    for ( i = 0; i < 2; i++ ) { 
      ds_values[ i ] = wb_distance_sensor_get_value( ds[ i ] );
    } // end for
    
    if ( ds_values[ 0 ] < 950 || ds_values[ 1 ] < 950 ) { 
      avoid_obstacle_counter = 100;
    } // end if
  } // end else

    /*
     * Enter here functions to send actuator commands, like:
     * wb_motor_set_position(my_actuator, 10.0);
     */
    wb_motor_set_velocity( wheel[ 0 ], left_speed );
    wb_motor_set_velocity( wheel[ 1 ], right_speed );
    wb_motor_set_velocity( wheel[ 2 ], left_speed );
    wb_motor_set_velocity( wheel[ 3 ], right_speed );
  }; // end while

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
