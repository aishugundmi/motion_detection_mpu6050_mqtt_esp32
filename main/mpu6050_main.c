/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <math.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_log.h"
#include "mqtt_client.h"

#include "i2c.h"
#include "MPU6050.h"
#include "MPU6050_HAL.h"


int32_t mean_resultant(void);
static const char *TAG = "MAIN_APP";

mpu_data_t mpu6050;
int32_t no_motion_resultant_acc;
extern esp_mqtt_client_handle_t client;

int32_t mean_resultant(void)
{
    int32_t arr[100], mean = 0;
    double std_deviation = 0, variance = 0;
    
    while(1){
        //finding mean value from 100 samples
        for(int i = 0; i < 100; i++){
            read_mpu(&mpu6050);  
            arr[i] = (int32_t) sqrt(pow((double)(mpu6050.Ax), 2) + pow((double)(mpu6050.Ay), 2) + pow((double)(mpu6050.Az), 2));	       
            mean += arr[i];	
        }
        mean /= 100;
        
        //finding standard deviation for collected 100 samples
        for(int i = 0; i < 100; i++){
            variance += pow((arr[i] - mean), 2);
        }        
        variance /= 100;
        std_deviation = sqrt(variance);
        
        printf("mean = %d\t SD = %f\n",  mean, std_deviation);
        
        if(std_deviation < 300){
            break;
        }
        else{
            ESP_LOGE(TAG, "calibration error, keep mpu6050 stable while calibrating\n");
        }
    }
    
    
	//printf("mean no_motion resultant acceleration = %d  (equivalent to  9.8 g )\n", temp);
   
   return mean;
}


void app_main_mpu6050(void)
{
    uint8_t data;
    printf("Hello world!\n");
	i2c_init();
    MPU6050_Init();
	i2c_read_byte(MPU6050_Address, MPU6050_RA_WHO_AM_I, &data);
	printf("%x\n", (int) data);
	
    int no_motion_cnt = 0;
    int free_fall_cnt = 0;
    int32_t resultant_acc = 0;
    no_motion_resultant_acc = mean_resultant();
    
    
    while (1)
    {
        vTaskDelay(50/10);
        read_mpu(&mpu6050);        
        resultant_acc = (int32_t) sqrt(pow((double)(mpu6050.Ax), 2) + pow((double)(mpu6050.Ay), 2) + pow((double)(mpu6050.Az), 2));
	//	printf("%d\n", resultant_acc);
     //   printf("%d,\t%d,\t%d\n", (int) mpu6050.Ax, (int) mpu6050.Ay, (int) mpu6050.Az);
		if((resultant_acc > (no_motion_resultant_acc + 3000)) ||  (resultant_acc < (no_motion_resultant_acc - 3000))){   //checking +- 2000 window for motion detection
			char buff[100];
            sprintf(buff, "%d motion detected\n", no_motion_cnt++);
            printf(buff);
            esp_mqtt_client_publish(client, "/gundmi/tx", buff, 0, 1, 0);            
			vTaskDelay(1000/10);   //100=1sec
		}
		if( resultant_acc < (no_motion_resultant_acc / 10)){   //checking +- 2000 window for motion detection
			printf("free-fall detected %d\n", free_fall_cnt++ );
			vTaskDelay(1000/10);   //100=1sec
		}
        
        
    }   
    
}
