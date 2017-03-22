#include <stdio.h>
#include <stdlib.h>

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
	char data_Type;
};

struct satellite_Data all_Data[];

struct satellite_Data get_SatelliteHealth();
struct satellite_Data get_ExperimentInfo();
void print_Summary(struct satellite_Data*);


int main()
{
	struct satellite_Data all_Data[MAX_DATA];

	int data_count = 0;
	int desired_Action = 0;

	do
	{
		// make sure we don't overrun your array....
		if (data_count == MAX_DATA)
		{
			// print error?
			// print_Summary(all_Data)?
			//return 0;
		}

		//prompt input
		printf("Please enter the number for the desired action (1, 2, 3): \n");

		//collect input
		scanf("%d\n", desired_Action);

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
		case 3:
			{
				print_Summary(all_Data);
			}
			return 0;
		default: ;
		}
	}
	while (desired_Action != 3);
	return 0;
}

struct satellite_Data get_ExperimentInfo()
{
	struct satellite_Data all_Data;

	// get data from user


	return all_Data;
}


struct satellite_Data get_SatelliteHealth()
{
	struct satellite_Data all_Data;
	float temperature;
	float voltage;
	printf("Enter the temperature: \n");
	scanf("%f\n", temperature);
	printf("Enter the voltage: ");
	scanf("%f\n", voltage);

	all_Data.data.health_Data.temperature = temperature;
	all_Data.data.health_Data.voltage = voltage;
	all_Data.data_Type = 'h';

	return all_Data;
}

void print_Summary(struct satellite_Data satellite_data[])
{
	// health totals
	long health_count = 0;
	float max_temperature = 0.0;
	float min_temperature = 0.0;

	//max_Health_Info.health.voltage = 0.0; - fix me
	//min_Health_Info.health.voltage = 0.0;

	// experiment totals
	long experiment_count = 0;
	// experiment_Total.experiment.radiation_count = 0;
	// experiment_Total.experiment.latchup_events = 0;

	int data_length = sizeof(satellite_data) / sizeof(struct satellite_Data);
	for (int i = 0; i < data_length; i++)
	{
		// total satellite health
		if (satellite_data[i].data_type == data.health_data;)
		{
			// incr health count
			// test for max / min

			if (satellite_data[i].data.health_Data.temperature > max_temperature)
			{
				max_temperature = satellite_data[i].data.health_Data.temperature;
			}

			if (temperature < min_Health_Info.health.temperature)
			{
				min_Health_Info.health.temperature = temperature;
			}

			if (voltage > max_Health_Info.health.voltage)
			{
				max_Health_Info.health.voltage = voltage;
			}

			if (voltage < min_Health_Info.health.voltage)
			{
				min_Health_Info.health.voltage = voltage;
			}
		}
		else
		{
			// total exeriment health
		}
	}

	// print out totals
}
