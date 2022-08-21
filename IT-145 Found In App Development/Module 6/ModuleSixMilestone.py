# Eric Wallace


# Main program procedure call
def main():

    current_room = "Great Hall"

    # Display instructions and game information to player
    def show_game_info():
        print('Currently, you are in the {}'.format(current_room))

    # A dictionary for the simplified dragon text game
    # The dictionary links a room to other rooms.
    rooms = {
        'Great Hall': {'South': 'Bedroom'},
        'Bedroom': {'North': 'Great Hall', 'East': 'Cellar'},
        'Cellar': {'West': 'Bedroom'}
    }

    # Function checks direction entered is valid
    def check_direction(move_direction, room):
        this_room = rooms.get(room)
        if move_direction in this_room:
            return True
        else:
            return False

    # Function moves player to next room
    def move_player(move_direction, room):
        this_room = rooms.get(room)
        next_room = this_room.get(move_direction)
        return next_room

    # Loop until exit is entered or exit room reached
    while True:
        action = ""
        direction = ""

        # Call to show game info
        show_game_info()

        # Prompt player to enter command
        commands = input("Enter a command!!\n").split()

        if commands[0] == "exit":
            current_room = "exit"
            show_game_info()
            print("You exited the game")
            break
        elif len(commands) != 2 or (commands[0] != "go" and commands[0] != "exit"):
            print('Error:  Invalid command entered, please try again')
            continue
        else:
            action = commands[0]
            direction = commands[1]
            # Action entered go to move player
            if action == "go":
                # Checks the validity of direction entered
                if check_direction(direction, current_room):
                    current_room = move_player(direction, current_room)
                    if current_room == "Cellar":
                        print("You have reached the end")
                        break
                else:
                    print("Error:  Invalid direction entered, please try again")
                    continue


main()
