// Jake Wade, CS 1324
/* This program reads simulated satellite telemetry from standard
input, performs a bit of analysis on that data and outputs a summary of the telemetry */

#include <stdio.h>  /* printf(), scanf() */
#include <stdlib.h>  /*  */
#include <math.h> // To access and execute INFINITY Macro for Float

#define MAX_DATA 100


enum DATA_TYPES
{
	health_data,
	experiment_data
};

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

const struct satellite_Data
{
	union satellite_Data_Union data;
	enum DATA_TYPES data_Type;
};

const struct satellite_Data get_SatelliteHealth();
const struct satellite_Data get_ExperimentInfo();

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

	int token_read = scanf("%d", &desired_Action);
    while(token_read != 1)
    {
        printf("\nError: Invalid input, choose again \n\n");
        fflush(stdin);
        printf("Please enter the number for the desired action (1, 2, 3): \n");
        printf("  1 - Enter a packet of satellite health information \n");
        printf("  2 - Enter a packet of experiment information \n");
        printf("  3 - Print summary information on the telemetry and exit the program\n");
        token_read = scanf("%d", &desired_Action);
    }

    while (desired_Action != 3 && data_count < MAX_DATA)
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
            printf("Error: Invalid input, choose again \n");
            fflush(stdin);
        }

    //prompt input
        printf("Please enter the number for the desired action (1, 2, 3): \n");
        printf("  1 - Enter a packet of satellite health information \n");
        printf("  2 - Enter a packet of experiment information \n");
        printf("  3 - Print summary information on the telemetry and exit the program\n");

        //collect input
        token_read = scanf("%d", &desired_Action);
        while(token_read != 1)
        {
            printf("\nError: Invalid input, choose again \n\n");
            fflush(stdin);
            printf("Please enter the number for the desired action (1, 2, 3): \n");
            printf("  1 - Enter a packet of satellite health information \n");
            printf("  2 - Enter a packet of experiment information \n");
            printf("  3 - Print summary information on the telemetry and exit the program\n");
            token_read = scanf("%d", &desired_Action);
        }
    }
    print_Summary(all_Data, data_count);
	return 0;
}



const struct satellite_Data get_ExperimentInfo()
{
	struct satellite_Data all_Data;

	// get data from user
    printf("Enter the radiation count: ");
	int token_rad = scanf("%u", &all_Data.data.experiment_Data.radiation_count);
	while (token_rad !=1)
    {
        printf("\nError: Invalid input, choose again \n\n");
        fflush(stdin);
        printf("Enter the radiation count: ");
        token_rad = scanf("%u", &all_Data.data.experiment_Data.radiation_count);
    }

	printf("Enter latchup events: ");
	int token_latch = scanf("%u", &all_Data.data.experiment_Data.latchup_events);
	while (token_latch !=1)
    {
        printf("\nError: Invalid input, choose again \n\n");
        fflush(stdin);
        printf("Enter latchup events: ");
        token_latch = scanf("%u", &all_Data.data.experiment_Data.latchup_events);
    }
	scanf("%u", &all_Data.data.experiment_Data.latchup_events);


    printf("\n");

    all_Data.data_Type = experiment_data;
	return all_Data;
}


const struct satellite_Data get_SatelliteHealth()
{
	struct satellite_Data all_Data;

	printf("Enter the temperature: ");
	int token_temp = scanf("%f", &all_Data.data.health_Data.temperature);
	while (token_temp != 1)
    {
        printf("\nError: Invalid input, choose again \n\n");
        fflush(stdin);
        printf("Enter the temperature: ");
	    token_temp = scanf("%f", &all_Data.data.health_Data.temperature);
    }

	printf("Enter the voltage: ");
	int token_volt = scanf("%f", &all_Data.data.health_Data.voltage);
	while (token_volt != 1)
    {
        printf("\nError: Invalid input, choose again \n\n");
        fflush(stdin);
        printf("Enter the voltage: ");
	    token_volt = scanf("%f", &all_Data.data.health_Data.voltage);
    }


	printf("\n");
	all_Data.data_Type = health_data;

	return all_Data;
}


void print_Summary(struct satellite_Data satellite_data[], int count)
{
	// health totals
	long health_count = 0;
	float max_temperature = -INFINITY;
	float min_temperature = INFINITY;

	float max_voltage = -INFINITY;
	float min_voltage = INFINITY;

	// experiment totals
	long experiment_count = 0;
    long experiment_Total_radiation = 0;
	long experiment_Total_latchup_events = 0;

	for (int i = 0; i < count; i++)
	{
		// total satellite health

		if (satellite_data[i].data_Type == health_data)
		{
			// incr health count
			// test for max / min

			health_count += 1;

			if (satellite_data[i].data.health_Data.temperature > max_temperature)
			{
				max_temperature = satellite_data[i].data.health_Data.temperature;
			}

			if (satellite_data[i].data.health_Data.temperature < min_temperature)
			{
				min_temperature = satellite_data[i].data.health_Data.temperature;
			}

			if (satellite_data[i].data.health_Data.voltage > max_voltage)
			{
				max_voltage = satellite_data[i].data.health_Data.voltage;
			}

			if (satellite_data[i].data.health_Data.voltage < min_voltage)
			{
				min_voltage = satellite_data[i].data.health_Data.voltage;
			}
		}
		else
		{
			// total experiment health
			experiment_count += 1;
			experiment_Total_radiation += satellite_data[i].data.experiment_Data.radiation_count;
			experiment_Total_latchup_events += satellite_data[i].data.experiment_Data.latchup_events;
		}
	}

  	if (health_count == 0)  // REVIEW good defensive programming!  kudos
  	{
   		max_temperature = 0;
   		min_temperature = 0;
   		max_voltage = 0;
   		min_voltage = 0;
  	}

	// print out totals
	printf("Number of satellite health information packets: %ld\n", health_count);
	printf("  Maximum temperature: %f\n", max_temperature);
	printf("  Minimum temperature: %f\n", min_temperature);
	printf("  Maximum voltage: %f\n", max_voltage);
	printf("  Minimum voltage: %f\n\n", min_voltage);
    printf("Number of experiment information packets: %ld\n", experiment_count);
    printf("  Total radiation count: %ld\n", experiment_Total_radiation);
    printf("  Total latchup events: %ld\n", experiment_Total_latchup_events);
}
