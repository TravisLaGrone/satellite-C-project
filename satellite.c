// Jake Wade, CS 1324
/* This program reads simulated satellite telemetry from standard
input, performs a bit of analysis on that data and outputs a summary of the telemetry */

#include <stdio.h>  /* printf(), scanf() */
#include <stdlib.h>  /*  */

#define MAX_DATA 100


enum DATA_TYPES
{
	health_data,
	experiment_data
} data;

struct health_info
{
	float temperature;
	float voltage;
};

struct experiment_info
{
	unsigned int radiation_count;
	unsigned int latchup_events;
};


union satellite_Data_Union
{
	struct health_info health_Data;
	struct experiment_info experiment_Data;
};

struct satellite_Data
{
	union satellite_Data_Union data;
	enum DATA_TYPES data_Type;
};

struct satellite_Data get_SatelliteHealth();
struct satellite_Data get_ExperimentInfo();


void print_Summary(struct satellite_Data saellite_data[], int count);


int main()
{
	struct satellite_Data all_Data[MAX_DATA];

	int data_count = 0;
	int desired_Action = 0;
	printf("Please enter the number for the desired action (1, 2, 3): \n");
	printf("  1 - Enter a packet of satellite health information \n");
    printf("  2 - Enter a packet of experiment information \n");
	printf("  3 - Print summary information on the telemetry and exit the program\n");

	scanf("%d", &desired_Action);

	while(desired_Action!=3)
	{
		switch (desired_Action)
		{
		case 1:
			{
				all_Data[data_count++] = get_SatelliteHealth();
			}
			break;
		case 2:
			{
				all_Data[data_count++] = get_ExperimentInfo();
			}
			break;

	     default:
	     	printf("Illegal Choice, choose again \n");
		}

		//prompt input
		printf("Please enter the number for the desired action (1, 2, 3): \n");
		printf("  1 - Enter a packet of satellite health information \n");
		printf("  2 - Enter a packet of experiment information \n");
		printf("  3 - Print summary information on the telemetry and exit the program\n");

		//collect input
		scanf("%d", &desired_Action);

	}

	print_Summary(all_Data, data_count);


	return 0;
}

struct satellite_Data get_ExperimentInfo()
{

	struct satellite_Data all_Data;
	unsigned int radiation_count;
	unsigned int latchup_events;



	// get data from user

    printf("Enter the radiation count \n");
	scanf("%u", &radiation_count);  // REVIEW pass the address of the variable, not its value!
	printf("Enter latchup events: ");
	scanf("%u", &latchup_events);  // REVIEW pass the address of the variable, not its value!
    printf("\n");

    all_Data.data.experiment_Data.radiation_count = radiation_count;
	all_Data.data.experiment_Data.latchup_events = latchup_events;
	all_Data.data_Type = experiment_data;


	return all_Data;
}


struct satellite_Data get_SatelliteHealth()
{
	struct satellite_Data all_Data;
	float t = 0.0;
	float v = 0.0;  // REVIEW put an empty line after this for readability

	printf("Enter the temperature: ");
	scanf("%f", &t);
	printf("Enter the voltage: ");
	scanf("%f", &v);
	printf("\n");
	 all_Data.data.health_Data.temperature = t;
	 all_Data.data.health_Data.voltage = v;
	 all_Data.data_Type = health_data;

	return all_Data;
}


void print_Summary(struct satellite_Data satellite_data[], int count)
{
	// health totals
	long health_count = 0;
	float max_temperature = -1000;
	float min_temperature = 5000;


	float max_voltage = -1000;
	float  min_voltage = 1000;

	// experiment totals
	long experiment_count = 0;
    long experiment_Total_radiation = 0;
	long experiment_Total_latchup_events = 0;


	int data_length = count;

	for (int i = 0; i < data_length; i++)
	{
		// total satellite health

		if (satellite_data[i].data_Type == health_data)
		{
			// incr health count
			// test for max / min
			float temperature = satellite_data[i].data.health_Data.temperature;
			float voltage = satellite_data[i].data.health_Data.voltage;
			health_count+=1;

			if (satellite_data[i].data.health_Data.temperature > max_temperature)
			{
				max_temperature = satellite_data[i].data.health_Data.temperature;
			}

			if (temperature < min_temperature)
			{
				min_temperature = temperature;
			}

			if (voltage > max_voltage)
			{
				max_voltage = voltage;
			}

			if (voltage < min_voltage)
			{
				min_voltage = voltage;
			}
		}
		else
		{
			// total experiment health
			experiment_count+=1;
			experiment_Total_radiation += satellite_data[i].data.experiment_Data.radiation_count;
			experiment_Total_latchup_events += satellite_data[i].data.experiment_Data.latchup_events;
		}
	}

   if(health_count==0){
   		max_temperature=0;
   		min_temperature=0;
   		max_voltage=0;
   		min_voltage=0;
   }

	// print out totals

	printf("Number of satellite health information packets: %ld\n",health_count);
	printf("  Maximum temperature: %f\n",max_temperature);
	printf("  Minimum temperature: %f\n", min_temperature);
	printf("  Maximum voltage: %f\n", max_voltage);
	printf("  Minimum voltage: %f\n\n",min_voltage);
    printf("Number of experiment information packets: %ld\n",experiment_count);
    printf("  Total radiation count: %ld\n", experiment_Total_radiation );
    printf("  Total latchup events: %ld\n", experiment_Total_latchup_events );
}
