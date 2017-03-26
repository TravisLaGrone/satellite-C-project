// Jake Wade, CS 1324
/* This program reads simulated satellite telemetry from standard input, performs
 * a bit of analysis on that data and outputs a summary of the telemetry
 */

#include <stdio.h>  // printf(), scanf()
#include <stdlib.h>  // REVIEW remove this, it's not used for anything
#include <math.h> // INFINITY

#define MAX_DATA 100

const char MENU_PROMPT[] =
	"Please enter the number for the desired action (1, 2, 3): \n"
	"  1 - Enter a packet of satellite health information \n"
    "  2 - Enter a packet of experiment information \n"
	"  3 - Print summary information on the telemetry and exit the program\n";

const char ERROR_MESSAGE[] = "\nERROR: Invalid input, choose again \n\n";



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

/* REVIEW
 * `const` doesn't do anything here.  The `const` modifier only applies to
 * variables, not directly to structure and function definitions.  So remove
 * the `const` here.  See http://stackoverflow.com/a/4267031/5029307 for comparison
 */
const struct satellite_Data
{
	union satellite_Data_Union data;
	enum DATA_TYPES data_Type;
};

/* REVIEW
 * `const` isn't necessary here, since you're returning the actual value itself
 * and not a pointer to the value.  When you return a `const` value from a function,
 * that means that it cannot be modified directly.  Normally, you would assign
 * the return value to a `const` variable.  However, it is possible to assign a
 * `const` return value to a non-`const` variable.  In that case, since the `const`
 * return value is not allowed to be modified, what happens is that a copy of it
 * is made before it is assigned to the non-`const` variable.  And that's basically
 * the same thing as simply returning a non-`const` value in the first place,
 * except that now you have the extra overhead of making an unnecessary copy.
 * So remove the `const` modifier on the return type for both of these functions.
 *
 * NOTE:  Returning a `const` type from a function is only useful if there are
 * pointers involved.  Either the return type is a pointer itself, or the return
 * type is a `struct` that has a pointer as a data member.  The reasons why are
 * a little bit complicated, so if you're curious then ask me in person.
 */
const struct satellite_Data get_SatelliteHealth();
const struct satellite_Data get_ExperimentInfo();

/* REVIEW
 * This is where `const` should be used.  Both of the parameters should be made
 * `const`.  I.e. "const struct satellite_Data" and "const int".
 *
 * Since the parameters are variables, it makes sense to make a parameter
 * `const`.  So when do you want to make a parameter `const`?  Whenever you
 * don't want the value of the parameter to be changed inside the function.
 *
 * On one hand, this might be because the variable should be a `const` naturally.
 * E.g. from the perspective of the function, the size of the array cannot be
 * changed, and so "count" is naturally a constant -- formally making it `const`
 * as well helps you to avoid accidentally changing the value of "count" since
 * it never makes sense to change it anyway.
 *
 * On the other hand, this might be because the variable actually references
 * (pointers to) data outside the function, and you don't want the function to
 * change data elsewhere.  Remember how we discussed that an array isn't actually
 * copied in to a function, but rather the function just gets the address of the
 * array?  Well, that means that from inside the function you could change the
 * values in the original array and those changes would be visible from outside
 * the function, even if the function doesn't return anything.  In some cases
 * this is useful.  But not for this function.  So making an array parameter
 * `const` is a way to ensure that a function doesn't accidentally screw up data
 * elsewhere that it's not supposed to change.
 */
void print_Summary(struct satellite_Data saellite_data[], int count);

/* REVIEW
 * In general, if a function parameter should not be changed inside the function,
 * then make it `const`.  Moreover, if any variable anywhere is naturally a constant,
 * then make it `const`.  Make as many variables / parameters `const` as you can
 * (within reason).  This will enable the compiler to help you catch more bugs
 * early on.
 */



int main()
{
	struct satellite_Data all_Data[MAX_DATA];

	int data_count = 0;
	int desired_Action = 0;

	printf(MENU_PROMPT);
	int tokens_read = scanf("%d", &desired_Action);
    while (tokens_read != 1)
    {
        printf(ERROR_MESSAGE);
        fflush(stdin);
        printf(MENU_PROMPT);
        tokens_read = scanf("%d", &desired_Action);
    }

    while (desired_Action != 3 && data_count < MAX_DATA)
    {
        switch (desired_Action)
        {
        case 1:
            all_Data[data_count++] = get_SatelliteHealth();
            break;

        case 2:
            all_Data[data_count++] = get_ExperimentInfo();
            break;

        default:
            printf(ERROR_MESSAGE);
            fflush(stdin);
			/* REVIEW
			 * `fflush()` is not necessary here because you can only reach the
			 * "default" case if the input was actually read, otherwise the
			 * problem would've been caught in the tokens-read while loop.  It
			 * just happens to be that the input here is a number other than
			 * 1, 2, or 3.
			 */
        }

    	// prompt next input
        printf(MENU_PROMPT);

        // collect next input
        tokens_read = scanf("%d", &desired_Action);
        while (tokens_read != 1)
        {
            printf(ERROR_MESSAGE);
            fflush(stdin);
            printf(MENU_PROMPT);
            tokens_read = scanf("%d", &desired_Action);
        }
    }
    print_Summary(all_Data, data_count);

	return 0;
}


const struct satellite_Data get_ExperimentInfo()
{
	struct satellite_Data data_packet;

	// get radiation_count from user
    printf("Enter the radiation count: ");
	int tokens_read = scanf("%u", &data_packet.data.experiment_Data.radiation_count);
	while (tokens_read !=1)
    {
        printf(ERROR_MESSAGE);
        fflush(stdin);
        printf("Enter the radiation count: ");
        tokens_read = scanf("%u", &data_packet.data.experiment_Data.radiation_count);
    }

	// get latchup_events from user
	printf("Enter latchup events: ");
	tokens_read = scanf("%u", &data_packet.data.experiment_Data.latchup_events);
	while (tokens_read !=1)
    {
        printf(ERROR_MESSAGE);
        fflush(stdin);
        printf("Enter latchup events: ");
        tokens_read = scanf("%u", &data_packet.data.experiment_Data.latchup_events);
    }
	scanf("%u", &data_packet.data.experiment_Data.latchup_events);  // REVIEW why is this here?

    printf("\n");

    data_packet.data_Type = experiment_data;
	return data_packet;
}


const struct satellite_Data get_SatelliteHealth()
{
	struct satellite_Data data_packet;

	// get temperature from user
	printf("Enter the temperature: ");
	int tokens_read = scanf("%f", &data_packet.data.health_Data.temperature);
	while (tokens_read != 1)
    {
        printf(ERROR_MESSAGE);
        fflush(stdin);
        printf("Enter the temperature: ");
	    tokens_read = scanf("%f", &data_packet.data.health_Data.temperature);
    }

	// get voltage from user
	printf("Enter the voltage: ");
	tokens_read = scanf("%f", &data_packet.data.health_Data.voltage);
	while (tokens_read != 1)
    {
        printf(ERROR_MESSAGE);
        fflush(stdin);
        printf("Enter the voltage: ");
	    tokens_read = scanf("%f", &data_packet.data.health_Data.voltage);
    }

	printf("\n");

	data_packet.data_Type = health_data;
	return data_packet;
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

  	if (health_count == 0)
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
