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
} data;  // REVIEW why is a global variable declared here?  it's never used anywhere

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

/* REVIEW
 * Make both of these parameters `const`.  That's a common defensive programming
 * technique to make sure you don't accidentally change the value of something
 * that shouldn't be changed while inside a function.  For a program this small,
 * it's probably not necessary.  But it's still a good practice to get into.
 * (make sure to update the definition header as well as the declaration header)
 */
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

	/* REVIEW
	 * What if data_count >= MAX_DATA?  Make sure to test for this condition in
	 * your while loop header as well, and then have an if statement after the
	 * while loop body that displays an appropriate message in case filling up the
	 * array was the reason the while loop abruptly ended.  (it's always nice
	 * to let the user know why the program did what it did)
	 */
	while (desired_Action != 3)
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

		/* REVIEW
		 * What if the user enters invalid data entirely?  E.g. they enter a word
		 * instead of a number.  Nothing will be assigned to `desired_Action`, and
		 * so the program will repeat the last command entered since `desired_Action`
		 * will keep its previous value.  This is clearly not what you want to
		 * happen if the user enters this type of invalid data.  I recommend
		 * adding another validation check here on the return value of "scanf"
		 * (see the documentation) to handle this case.
		 * See http://stackoverflow.com/a/10084311/5029307
		 *
		 * NOTE:  This wasn't a problem for the priming read before you entered
		 * the while loop since you had already initialized desired_Action to 0,
		 * which would result in the "default" case executing and an error message
		 * correctly being displayed anyway.  But that doesn't apply here.
		 * Now that I think about it... you could just set desired_Action to 0
		 * again before this scanf, and that would solve the issue.  However,
		 * that is a somewhat non-intuitive approach, and I doubt it would be
		 * portable.  So I recommend using the better (more generalizable and
		 * more maintainable) defensive programming technique of just doing
		 * a true validation check on the return value of scanf.
		 */

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

	/* REVIEW
	 * What happens if the user enters invalid data?  E.g. the user enters a word
	 * instead of a number, or a number with two decimal points, or something else
	 * weird.  (hint: look at the documentation for the return value of "scanf")
	 * Make sure to handle this case for each scanf.  I recommend using a priming
	 * read followed by a while loop in case of incorrecty input that displays
	 * an error message and gets the value again.  Do this independently for
	 * each variable.
	 * See http://stackoverflow.com/a/10084311/5029307
	 */

	// get data from user
    printf("Enter the radiation count \n");
	scanf("%u", &radiation_count);
	printf("Enter latchup events: ");
	scanf("%u", &latchup_events);
    printf("\n");

	/* REVIEW
	 * Technically, you don't need local variables for `radiation_count` and
	 * `latchup_events`.  If you want more efficient space usage (if you didn't
	 * then why are you using C in the first place), then just pass the address
	 * of `all_Data.data.experiment_Data.radiation_count` and
	 * `all_Data.data.experiment_Data.latchup_events` to scanf directly.
	 */

    all_Data.data.experiment_Data.radiation_count = radiation_count;
	all_Data.data.experiment_Data.latchup_events = latchup_events;
	all_Data.data_Type = experiment_data;

	return all_Data;
}


struct satellite_Data get_SatelliteHealth()
{
	struct satellite_Data all_Data;

	/* REVIEW
	 * Why are both of these initialized?  I guess it doesn't hurt anything, but
	 * it will waste a couple processor cycles.  (and if you didn't care about
	 * maximum efficiency, then why are you using C in the first place)
	 */
	float t = 0.0;
	float v = 0.0;

	/* REVIEW
	 * What happens if the user enters invalid data?  E.g. the user enters a word
	 * instead of a number, or a number with two decimal points, or something else
	 * weird.  (hint: look at the documentation for the return value of "scanf")
	 * Make sure to handle this case for each scanf.  I recommend using a priming
	 * read followed by a while loop in case of incorrecty input that displays
	 * an error message and gets the value again.  Do this independently for
	 * each variable.
	 * See http://stackoverflow.com/a/10084311/5029307
	 */

	printf("Enter the temperature: ");
	scanf("%f", &t);
	printf("Enter the voltage: ");
	scanf("%f", &v);
	printf("\n");

	/* REVIEW
	 * Technically, you don't need local variables for `t` and
	 * `v`.  If you want more efficient space usage (if you didn't
	 * then why are you using C in the first place), then just pass the address
	 * of `all_Data.data.health_Data.temperature` and
	 * `all_Data.data.health_Data.voltage` to scanf directly.
	 */

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
	float min_voltage = 1000;

	/* REVIEW
	 * Are the default values for max and min temperature and voltage true limits
	 * for your application, or just arbitrary numbers?  If it's the former, then
	 * you're good.  But if it's the latter, then this could be buggy.  A safer
	 * and more general alternative is to use the macros in the "float.h" header file.
	 */

	// experiment totals
	long experiment_count = 0;
    long experiment_Total_radiation = 0;
	long experiment_Total_latchup_events = 0;


	int data_length = count;  // REVIEW why don't you just use `count` directly?

	/* REVIEW
	 * Ideally, any index variable should be of type `size_t` (from the "stdlib.h"
	 * header file).  This guarantees that the type of the index is large enough
	 * to accurately represent the size of any array or data structure that could
	 * be created on a particular platform.  For a program this small, it doesn't
	 * matter.  But it is an important defensive programming technique.
	 */
	for (int i = 0; i < data_length; i++)
	{
		// total satellite health

		if (satellite_data[i].data_Type == health_data)
		{
			// incr health count
			// test for max / min

			/* REVIEW
			 * Why do you need extra local variables here?  Why not just use
			 * `satellite_data[i].data.health_Data.whatever` directly?  The
			 * processor will automatically cache their values anyway.
			 */
			float temperature = satellite_data[i].data.health_Data.temperature;
			float voltage = satellite_data[i].data.health_Data.voltage;
			health_count += 1;

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
