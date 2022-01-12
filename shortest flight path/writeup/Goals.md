

CS225 Proposal

**Leading Question**

The problem we’re trying to solve is to ﬁnd the path between two airports with the least

number of stops required. Layovers can often be time consuming and stressful, and

people usually want to reach their destination with as little time wasted as possible. As

such, we hope to allow users to input a departure and arrival airport and use our

program to determine the route they can take with the least number of layovers.

**Dataset Acquisition and Processing**

We have chosen the Open Flights airport

([https://raw.githubusercontent.com/jpatokal/openﬂights/master/data/airports.dat](https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat))

and route

([https://raw.githubusercontent.com/jpatokal/openﬂights/master/data/routes.dat](https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat))

database. We decided to use both databases so that we could have complete

information regarding what routes were available between airports as well as the exact

source and destination of a route. Both datasets are presented as CSVs, with the

Airports dataset containing information regarding airport ID, name, city, country, IATA

code, ICAO code, latitude, longitude, altitude, timezone, dst, tz database timezone, type

and source. The route database contains information regarding the airline IATA/ICAO

code, airline ID, source airport IATA/ICAO code, source airport ID, destination airport

IATA/ICAO code, destination airport ID, codeshare status, number of stops, and

equipment code. Since both datasets contain the airport IATA/ICAO codes, we will use

the IATA/ICAO code from the route dataset to determine the name and location of an

airport from the airports dataset.

Both datasets are represented by CSVs, and thus we can iterate over the data and store

relevant information to our search by storing each line in an array/vector of strings that

splits the line by comma.

Since we are working with real world data, it is possible that the data can be incorrect at

times. To handle cases where data is incorrect, we will be cross referencing our input

across both datasets. In a case where the data does not match, we will ignore the input

and continue with the next item. Also, if the data does not contain validIATA/ICAO code,

we will consider it as being invalid and continue as well, as our primary means of cross

referencing data is through the IATA/ICAO codes.

**Graph Algorithms**

BFS:





-we will use BFS to traverse through all the airports and the ﬂights connecting them to

ﬁnd the least number of layover stops given a starting and ending location. Our input

will be a starting and ending point and our output will be the route with the least number

of layover stops. Our worst case time complexity will be O(|V| + |E|) where V represents

vertices and E represents edges.

Dijkstra’s Algorithm:

\- we will use Dijkstra’s Algorithm and long and lat coordinates to calculate the shortest

path between two airports using the distance. Our input will be the long and lat coords

of a starting and destination airport and our output will be the distance between the two

coordinates.

**O((n+e)lg(n))**

Graphic Output of Graph:

-we will project onto a map based on data. We will use points to represent airport

locations where there was a visited stop and use lines to connect them to give the user

a visual representation to aid them in visualizing their journey. Our input will be long and

lat coordinates representing points along a route between a starting and destination

point. Our output will be a visual representation of these points connected on a map.

We’d most likely need to loop through the points so the worst time complexity would be

O(N^2) as it’d need to loop through both the long and lat coords on the map.

Backup Option:

Betweenness Centrality:

-we will use Betweenness Centrality to ﬁnd the airport with most ﬂights in and out of it

to recommend more security to a certain airport or recommend an airport to a

passenger so they are more likely to ﬁnd a ﬂight even with delays and cancellations. We

believe the worst-case runtime would be O(N \* E) where N is nodes and E is edges.

**Timeline**

End of this week (11/7-11/13) - Have “progress paragraph” added for this week.

Complete Proposal and Contract and discuss initial ideas without writing code.

Week of 11/14 - complete data acquisition and processing this week. Add another

“progress paragraph”.

Week of 11/21 - complete constructors in the ﬁrst half of the week and BFS traversal in

the second half of the week.

Week of 11/28 - ﬁnish BFS traversal earlier in the week if not completed. Meet with

mentor and get some feedback. Use Dijkstra’s Algorithm to get optimal paths between

airports using distance.





Halfway point (11/29 - 12/1) - have data acquisition and processing complete. Have

constructors completed for structure. Have at least BFS done.

Anything from this point on is subject to change depending on our position at the

halfway point

Week of 12/1 Finish Graphic implementation

Week of 12/7 Work on Presentation

Deadline (12/13) - Project Presentation and Project Code Finished

