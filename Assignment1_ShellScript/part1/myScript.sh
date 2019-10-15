# Problem statement: I am a fan of Liverpool, an English soccer team. Often I want to check and 
# see if the team is playing today, but that generally requires opening google and sorting through
# the schedule. This script allows me to see whether or not Liverpool plays today, who they play,
# if they are home or away, and what time (converted to eastern standard) they play at. It also
# tells me if there are upcoming fixtures and the dates/times of those fixtures.

# usage: sh myScirpt.sh

# curl command does an HTTP GET request at the specified URL. the ">" symbol stores the data
# retrieved by the curl in a file called "lvFixtures.csv"
curl -s https://fixturedownload.com/download/epl-2019-liverpool-GMTStandardTime.csv > lvFixtures.csv

# variable $date_today gets the current date using the date command. "date" accepts a format specifier
# seen after the + sign. In this case I format todays date in DD/MM/YYYY format to match the format
# of the dates provided in the csv file.
date_today=$(date +%d/%m/%Y)
game_today=false

# this function converts the game times in the csv from UCT to EST.
uct_to_est() {
	# times are given in HH:MM format. Use "cut" command to get the hours and minutes
	# use "-d:" to split the time between the colon, -f1 refers to the first argument before ":" (hours),
	# and -f2 the grabs the second argument (minutes)
	# "cut" is applied to the argument provided before the "|" symbol, in this case $1.
	# $1 refers to the first argument passed in to the function.
	given_hr=$(echo $1 | cut -f1 -d:)
	given_min=$(echo $1 | cut -f2 -d:)
	# subtract 5 from the given hour to convert UCT->EST
	est_hr=$(($given_hr-5))
	if [ $est_hr -lt 0 ]; then
		est_hr=$(($given_hr+24))
	fi
	# reformat back to HH:MM
	est_time="$est_hr:$given_min"
}

# compare_dates() : For each game, call this function to see whether the game date matches todays date
compare_dates() {
	# Use cut again, with / as our delimiter to extract month, day, and year of game
	month=$(echo $1 | cut -d "/" -f1)
	day=$(echo $1 | cut -d "/" -f2)
	yr=$(echo $1 | cut -d "/" -f3) 
	# Do the same for todays date
	this_month=$(echo $date_today | cut -d "/" -f1)
	this_day=$(echo $date_today | cut -d "/" -f2)
	this_yr=$(echo $date_today | cut -d "/" -f3)

	# compare  year, month, and day using nested conditional blocks
	if [ $yr == $this_yr ]
	then
		if [ $month == $this_month ]
		then
			if [ $day == $this_day ]
			then
				game_today=true
				# convert time with previously defined function
				uct_to_est $game_time

				# echo (print to terminal) our findings!
				echo 'Game today at' $est_time 'EST :' $home '(H) vs' $away '(A)'
			fi
		fi
	fi
}

# The code below parses the csv file.
# The while loop reads through the file passed at the end ("done < lvFixtures.csv")
# by applyring the read command to each row of the csv. each argument after "read" stores the data
# from the corresponding field into that variable, overwriting the value every loop. Essentially
# these names are the column headers from the csv file.
# IFS="," makes sure the read function knows each field is separated by a comma.
IFS=","
upcoming_fixtures=0
while read round date loc home away result
do
	# get game date and time for each game using date + format specifiers described earlier
	# the date column provides both day and time of game, but we would like this information separately.
	# awk is used in a similar manner as cut. "-F' '" sets space to be our delimiter, as the day and time
 	# are separated by a space. '{print $1}' assigns whatever is found before the space to the variable,
	# while '{print $2}' finds the first value after the delimiter. Finally <<< "$date" tells the command
	# that we want to awk the value in variable $date.
	game_date=$(date +%d/%m/%Y | awk -F' ' '{print $1}' <<< "$date")
	game_time=$(date +%H:%M | awk -F' ' '{print $2}' <<< "$date")
	
	# compare date for each game using previously defined function
	compare_dates $game_date
	
	# here, we wish to check for upcoming games. The first row in the csv will have the $game_date variable
	# set to 'Date' which we ignore in the first conditional. We also only want to know the next 5 games,
	# so we track how many upcoming matches we have already printed in $upcoming fixtures
	if [ $game_date != 'Date' -a $upcoming_fixtures -lt 6 ]
	then
		# this conditional checks if the $result variable contains a number, i.e. if the game has already happened.
		# if not, we print out some info about the upcoming match
		if [[ ! $result =~ [0-9] ]]; then	
			# Convert time, print info, and increment $upcoming fixtures
			uct_to_est $game_time
			echo 'Happening soon:' $game_date $est_time $home '(H) vs' $away '(A)'
			upcoming_fixtures=$(($upcoming_fixtures+1))
		fi		
	fi
	
done < lvFixtures.csv

# reset IFS to whatever value it was before the script, which is stored in environment variable $OLDIFS
IFS=$OLDIFS

# Command rm removes a given file. Here we do not need to keep the csv, as we want to redownload each time in case
# the schedule changes.
rm lvFixtures.csv

