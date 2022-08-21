# Import date to calculate birth year
import datetime

# Prompt user for name and save to variable
name = input('What is your name? ')

# Prompt user for age that will only accept integers and then save to variable
age = int(input('How old are you? '))

# Use datetime module to get current year
curr_year = datetime.date.today().year

# Calculate birth year
birth_year = curr_year - age

# Output string using print while using format to insert variables into string
print('Hello {0}!  You were born in {1}.'.format(name, birth_year))
