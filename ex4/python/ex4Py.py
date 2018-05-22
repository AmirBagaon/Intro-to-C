import string


def Initialize(database):
    """
     Explanation: Build a dictionary database from a file

     Keyword argument:
     database - the dictionary of movies (keys) and actors (values)

     Return:
     """

    # opens the file movies.txt
    with open('movies.txt') as file:
        for line in file:
            # Deletes the whitespaces ('/n', ' ') at start and end of each line
            row = line.strip()
            # each word (seperated by ', ') in row will be organ of "words" list
            words = row.split(', ')
            # Deletes the whitespaces of each organ (name of actor/movie)
            for i in range(len(words)):
                words[i] = words[i].strip()

            #Convert each name (word) to lower letters
            words=[name.lower() for name in words]
            #set the first word to be the actor, and the others to be movies
            actor = words[0]
            movies = words[1:]

            for movieName in movies:
                #if the movie's name is already a key in database
                if movieName in database:
                    #add the new actor to to be another value of this key
                    database[movieName].append(actor)
                else:
                    #set the movie's name as a new key of database
                    database[movieName] = [actor]


def FirstOption(database):
    """
    Explanation: get 2 movies and operator
    If the operator is '|': prints the union of the actors of the 2 movies
    If it is '&': prints the intersection of the actors of the 2 movies
    If it is '^': prints the symmetric difference of the actors of the 2 movies

    Keyword argument:
    database - the dictionary of movies (keys) and actors (values)

    Return:
    """

    #get 2 movies and operator
    print "Please enter two movies and an operator(&,|,^) separated with ',':"
    choice = raw_input()

    #split the input to 3 expressions (movie,movie,operator)
    for parts in choice:
        expression = choice.split(',')

    # delte whitespaces in each organ
    for i in range(len(expression)):
        expression[i] = expression[i].strip()

    #lower capital letters
    expression = [word.lower() for word in expression]

    #set variables for expression[0]/[1]/[2] so it be more readable
    firstMovie = expression[0]
    secondMovie = expression[1]
    operator = expression[2]
    #print error if the first or second movie isn't a key in database
    if (firstMovie not in database.keys()):
        print "Error"
        return
    if (secondMovie not in database.keys()):
        print "Error"
        return

    #call the appropriate function for the operator and insert it to list "temp"
    if operator == '|':
        temp = Union(database[firstMovie], database[secondMovie])
    elif operator == '&':
        temp = Intersection(database[firstMovie], database[secondMovie])
    elif operator == '^':
        temp = Symmetric(database[firstMovie], database[secondMovie])

    #if temp is empty
    if not temp:
        print "There are no actors in this group."
    else:
        #call a function that sort "temp" and print it with capital starting letters
        PrintCapitals(temp)


def Union(firstMovie, secondMovie):
    """
    Explanation: get 2 list of actors in a movie,
    and returns a list of the union of the actors of both movies

    Keyword argument:
    firstMovie - a list of actors in a movie
    secondMovie - a list of actors in another movie

    Return: the list "temp" that contains the union of the actors
    of both movies
    """

    #build a list "temp" and insert the union of both movies's actors
    temp = list(set(firstMovie) | set(secondMovie))
    #print if temp isn't empty
    if temp:
        print "The union actors are:"
    return temp


def Intersection(firstMovie, secondMovie):
    """
    Explanation: get 2 list of actors in a movie,
    and returns a list of the intersection of the actors of both movies

    Keyword argument:
    firstMovie - a list of actors in a movie
    secondMovie - a list of actors in another movie

    Return: the list "temp" that contains the intersections of the
    actors of both movies
    """

    # build a list "temp" and insert the intersection of both movies's actors
    temp = list(set(firstMovie) & set(secondMovie))
    # print if temp isn't empty
    if temp:
        print "The intersection actors are:"
    return temp


def Symmetric(firstMovie, secondMovie):
    """
    Explanation: get 2 list of actors in a movie,
    and returns a list of the symmetric difference of the actors
    of both movies

    Keyword argument:
    firstMovie - a list of actors in a movie
    secondMovie - a list of actors in another movie

    Return: the list "temp" that contains the symmetric differences
    of the actors of both movies
    """

    # build a list "temp" and insert the symmetric difference of the actors
    temp = list(set(firstMovie).symmetric_difference(set(secondMovie)))
    # print if temp isn't empty
    if temp:
        print "The symmetric difference actors are:"
    return temp


def PrintCapitals(listOne):
    """
    Explanation: get a list, sort it, and print each word with
    capital first letter

    Keyword argument:
    listOne - a list of strings of movies or actors

    Return:
    """

    #sort the list
    listOne.sort()

    listTwo = []
    #make each word in listOne to start with capital letter
    for organ in listOne:
        organ = string.capwords(organ)
        #add the word to listTwo
        listTwo.append(organ)

    #insert ', ' between each word, and print it all
    str = ", "
    str = str.join(listTwo)
    print str


def secondOption(database):
    """
    Explanation: get an actor name and print the name of all other
    actors (co-stars) that played with him in any movie in the database.

    Keyword argument:
    database - the dictionary of movies (keys) and actors (values)

    Return:
    """

    print "Please enter an actor:"
    choice = raw_input()
    #lower the capital letters of the input
    choice = choice.lower()
    #delte whitespaces in the input
    choice = choice.strip()

    #create a list of all the keys in the database, and an empty list
    temp = database.keys()
    stars = set()

    #create a "flag" that sign the actor is in the database
    flag = 0

    #run on the keys (movies names) in database
    for movie in temp:
        #if the actor is a value of some key
        if choice in database[movie]:
            #raise the "flag" and sign the actor is in the database
            flag = 1
            #add all the values in this key to the set we created before
            for actors in database[movie]:
                stars.add(actors)
        #discard the value of the original actor (we want to find only co-stars)
        stars.discard(choice)

    #if the "flag" hasn't raised-up, the actor is not in the database
    if flag == 0:
        #print error and return to menu
        print "Error"
        return

    #turn the set into a list in order to send it to PrintCapitals function
    coStars = list(stars)

    #if the list is empty
    if not coStars:
        print "There are no actors in this group."
    else:
        print "The actor's co-stars are:"
        #sort the list and print it with capital starting letters
        PrintCapitals(coStars)



"""
Main program,

Crate a database from a file,
and get a number from user.

For 1: Get 2 names of movies and an operator,
    If the operator is '|': prints the union of the actors of the 2 movies
    If it is '&': prints the intersection of the actors of the 2 movies
    If it is '^': prints the symmetric difference of the actors of the 2 movies

For 2: Get an actor name and print the name of all other
    actors (co-stars) that played with him in any movie in the database.

For 3: End the program
"""


#creat the database
database = {}
Initialize(database)

print "Processing..."
number = 0

#run as long as the input isn't 3
while number != '3':
    print "Please select an option:"
    print "1) Query by movies"
    print "2) Query by actor"
    print "3) Quit"

    #get a number and act
    number = raw_input()
    if number == '1':
        FirstOption(database)
    if number == '2':
        secondOption(database)