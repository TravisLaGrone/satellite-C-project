// TODO project synopsis / identifying info goes here

//////////////////
// HEADER FILES //
//////////////////
#include <stdio.h>  /* printf(), scanf() */
#include <stdlib.h>  /*  */



////////////
// MACROS //
////////////
#define MAX_DATA 100



//////////////////////
// TYPE DEFINITIONS //
//////////////////////

/* REVIEW
 * `typedef` each of your `struct`s and `enum`s, then remove the `struct` before
 * the type of each variable you declare of that type in the rest of your code.
 * This isn't strictly necessary, but it's a good practice for defensive programming.
 * See http://stackoverflow.com/a/1675446/5029307
 */

/* REVIEW
 * I don't think you understand how `enum`s work.  An enum is a programmer-defined
 * type that can take any of the values listed within the enum definition.
 * So you could say "enum DATA_TYPES my_variable = health_data;" and then later
 * do "if (my_variable == health_data)". Read http://en.cppreference.com/w/c/language/enum
 */
enum DATA_TYPES
{
	health_data,
	experiment_data
} data;  /* REVIEW
		  * You don't need to define a global variable here, since you only need a
		  * variable of type "DATA_TYPES" inside your "satellite_Data".  You can
		  * remove this.  (although you should replace it with an appropriate
		  * identifier for your typedef, as mentioned above).
		  */

/* REVIEW
 * It's not strictly necessary, but I recommend appending "_t" to the type
 * identifier of each struct since you're using a descriptive camel case name
 * anyway.  This "_t" is common practice to indicate that an identifier is a
 * programmer-defined type, and it can help disambiguate things when your variable
 * name will be very similar to the typename.
 */

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

/* REVIEW
 * snake_case or camelCase, pick one.  (just don't use both at the same time)
 * Make sure to update this in the rest of your code as well.  Again, it's not
 * strictly necessary, but it makes your code easier to read, easier to review,
 * and just more consistent and easily maintainable overall.
 *
 * On a side note, most C programmers prefer snake_case, sometimes using a
 * trailing "_t" to indicate user-defined types.  However, if you do want to use
 * camelCase, then type identifiers should use UpperCamelCase and everything else
 * (i.e. functions, variables) should use lowerCamelCase.
 */

union satellite_Data_Union
{
	struct health_info health_Data;
	struct experiment_info experiment_Data;
};

struct satellite_Data
{
	union satellite_Data_Union data;
	char data_Type;  /* REVIEW
					  * This should be of type `enum DATA_TYPES` (or its
					  * typedef'd identifier).
					  */
};



////////////////
// PROTOTYPES //
////////////////

/* REVIEW
 * You might think this is a prototype / forward declaration, but it's not.
 * This statement actually defines a global variable.  It's type is
 * "struct satellite_Data []".  It's identiier is "all_Data".  And it's size is
 * one (if no size is given, then it defaults to one).  See the attached file
 * "shadowing.c" that I put together to understand what is going on here.
 *
 * Even if this were a forward declaration of the "all_Data" variable you define
 * inside `main()`, you wouldn't need it anyway.  You can remove this line.
 */
struct satellite_Data all_Data[];

struct satellite_Data get_SatelliteHealth();
struct satellite_Data get_ExperimentInfo();

/* REVIEW
 * Unless you want to change the pointer itself (i.e. to a local array inside
 * the function) or the data behind the pointer (i.e. the data in the array),
 * then make this a `const` pointer to a `const` type.  Again, not strictly
 * necessary, but it's good defensive programming.  It helps you accidentally
 * avoid changing data where you don't want to, since you will get a compile-time
 * error if you try to change the value of something labelled `const`.  (remember
 * to update the header of your definition, too) See http://stackoverflow.com/a/4949299/5029307
 * and http://stackoverflow.com/questions/4949254/const-char-const-versus-const-char/4949299#comment56097244_4949299
 */
void print_Summary(struct satellite_Data*);



//////////
// MAIN //
//////////

int main()
{
	struct satellite_Data all_Data[MAX_DATA];

	int data_count = 0;
	int desired_Action = 0;

	do
	{
		// make sure we don't overrun your array....
		if (data_count == MAX_DATA)  /* REVIEW use "<=" for good defensive programming
									  * Trust me, this will be important on larger
									  * programs where very weird bugs can occur
									  */
		{
			// print error?
			// print_Summary(all_Data)?
			//return 0;
		}

		//prompt input
		printf("Please enter the number for the desired action (1, 2, 3): \n");
		/* REVIEW
		 * Where is the rest of the menu?  How will the user know what actions
		 * the numbers refer to?
		 */

		//collect input
		scanf("%d\n", desired_Action);  /* REVIEW don't use "\n" here, it doesn't
										 * make sense since you're not printing
										 * anything, you're just telling scanf
										 * what the type of your variable is
										 * (the "%d" part)
										 */

		switch (desired_Action)
		{
		case 1:
			{  /* REVIEW braces aren't necessary inside after a `case` since
				* `case` is just a label, not a block header (that's why you
				* have to use `break` instead of just closing a block)
				*/
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
			return 0;  /* REVIEW
						* Remove this.  Let control flow reach the normal `return`
						* at the end of main().  You don't want your code to randomly
						* jump around in the middle of functions (this includes
						* returning from the function or exiting the program).  In a
						* program this small it probably doesn't matter, but for
						* larger programs keeping your control flow obvious (i.e.
						* only one `return` statement in a function) will make your
						* code so much easier to debug and maintain.
						*/
			/* REVIEW
			 * Put a `break` here.  That way, just in case you do add anything to
			 * `default` in the future, you don't end up with a bug because you
			 * forgot that you didn't have a `break` in case 3.  Again, this is
			 * just good defensive programming.
			 */
		default: ;  /* REVIEW
					 * You don't need a default if it doesn't do anything.
					 * However, I would personally recommend putting an error
					 * message here telling the user that their choice was
					 * invalid.  Otherwise, the do-while loop will simply repeat,
					 * the menu will be displayed again, and the user will be left
					 * wondering what in the world just happened in response to
					 * their (albeit nonsensical) input.
					 */
		}
	}
	while (desired_Action != 3);

	return 0;
}

struct satellite_Data get_ExperimentInfo()
{
	/* REVIEW
	 * Poor choice of varibale name.  "all_Data" is already used to mean
	 * something in main(), so this is just confusing.  Technically, your code
	 * will still work since this scope doesn't clash with the scope in main(),
	 * but I would still change it to a better variable name.
	 */
	struct satellite_Data all_Data;

	// get data from user


	return all_Data;
}


struct satellite_Data get_SatelliteHealth()
{
	/* REVIEW
	 * See my first comment inside get_ExperimentInfo() about variable names.
	 */
	struct satellite_Data all_Data;
	float temperature;
	float voltage;  // REVIEW put an empty line after this for readability
	printf("Enter the temperature: \n");
	scanf("%f\n", temperature);  // REVIEW pass the address of the variable, not its value!
	printf("Enter the voltage: ");
	scanf("%f\n", voltage);  // REVIEW pass the address of the variable, not its value!
	// REVIEW see lines 12, 15 in the example code here http://www.cplusplus.com/reference/cstdio/scanf/

	all_Data.data.health_Data.temperature = temperature;
	all_Data.data.health_Data.voltage = voltage;
	all_Data.data_Type = 'h'; /* REVIEW
							   * After you change the type of `data_Type` from
							   * `char` to `enum DATA_TYPES` (or its typedef'd
							   * identifier), then assign health_data to it
							   * instead of 'h'
							   */

	return all_Data;
}

/* REVIEW
 * Although it looks like you are passing an array to this function, what you
 * are actually doing is passing a pointer (the array decays to a pointer
 * behind-the-scenes).  Why?  See http://stackoverflow.com/a/38859040/5029307
 * What this means is that you CANNOT find the size of the array inside the
 * function.  You HAVE to pass a second parameter indicating the size of the
 * array.  (when you change the function header to do this, remember to change
 * both the declaration and the definition, as well as any invocation [i.e.
 * where you actually use the function])
 *
 * On a side note, this definition uses "struct satellite_data []" but your
 * prototype / declaration uses "struct satellite_data *".  Don't do that.  Be
 * consistent.  And in your case, I would recommend using "*" to help yourself
 * remember that an array decays to a pointer when you pass it to a function.
 */
void print_Summary(struct satellite_Data satellite_data[])
{
	// health totals
	long health_count = 0;
	float max_temperature = 0.0;
	float min_temperature = 0.0;

	/* REVIEW
	 * You don't need a struct to store this data, unlike how you had to use a
	 * struct inside your union.  Just use an individual variable for each statistic,
	 * e.g. `float max_voltage;` and `float min_voltage`
	 * and `unsigned int total_radiation_count;` etc.
	 *
	 * Also, make sure you either use a priming run of the loop to initialize
	 * each variable or give each variable an appropriate default value.  (0.0
	 * is not an appropriate value for min / max calculations, the smallest / largest
	 * possible value of your data type is  ...although really, a priming run is
	 * usually the best option for a variety of reasons)
	 * See http://stackoverflow.com/a/1042523/5029307 for pseudocode of each style
	 */

	//max_Health_Info.health.voltage = 0.0; - fix me
	//min_Health_Info.health.voltage = 0.0;

	// experiment totals
	long experiment_count = 0;
	// experiment_Total.experiment.radiation_count = 0;
	// experiment_Total.experiment.latchup_events = 0;

	/* REVIEW
	 * This trick for getting the size of an array is correct, idiomatic C.
	 * Unfortunately, it won't work here for the reasons I stated in the comment
	 * immediately above this function.
	 */
	int data_length = sizeof(satellite_data) / sizeof(struct satellite_Data);
	for (int i = 0; i < data_length; i++)
	{
		// total satellite health
		/* REVIEW
		 * Think:  does this code make sense?  `satellite_data[i].data_type` is
		 * of type `char`, but `data` is of type `enum DATA_TYPES`.  Always make
		 * sure your types match up.  If they don't, that's a pretty good sign
		 * that there's a problem.  Also, this isn't the syntax for how you use
		 * enums.  See my comment just above your enum definition for how to use enums.
		 */
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
