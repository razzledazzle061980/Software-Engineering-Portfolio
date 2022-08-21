# Eric Wallace
# Escaped Prisoner, the player will move between rooms collecting
# parts to a shotgun, the goal is to collect all the gun parts before
# encountering the prisoner.

import time

item_count = 0
notification = ''

ERROR = ""
INFO = ""
SUCCESS = ""
WARNING = ""
RESET = ""
BOLD = ""
NORMAL = ""


def colors():
    global ERROR, INFO, SUCCESS, WARNING, RESET, BOLD, NORMAL
    NORMAL = '\033[37m'
    ERROR = '\033[91m'
    INFO = '\033[94m'
    SUCCESS = '\033[92m'
    WARNING = '\033[93m'
    RESET = '\033[0m'
    BOLD = "\033[1m"


def info(message, title=''):
    print(INFO + BOLD + title.upper() + RESET, INFO + message.capitalize() + RESET)


def success(message, title=''):
    print(SUCCESS + BOLD + title.upper() + RESET, SUCCESS + message + RESET)


def warning(message, title=''):
    print(WARNING + BOLD + title.upper() + RESET, WARNING + message + RESET)


def error(message, title=''):
    print(ERROR + BOLD + title.upper() + RESET, ERROR + message + RESET)


# Function shows game over information
def show_game_over(outcome):
    error('-----------------------------------------------------------------------')
    error('                      Escaped Prisoner                                 ')
    error('-----------------------------------------------------------------------')
    print("You are in the Basement")
    print("You see the prisoner:  ")
    if outcome == "win":
        success("Congratulations, you win!!  You collected all the items, assembled the gun,")
        success("and apprehended the prisoner.")
        success("Thank You for playing!!")
    elif outcome == "lost":
        warning("Sorry, you lost!!  You failed to collect all the parts and have been taken")
        warning("hostage by the prisoner.")
        warning("Thank You for playing!!")
    print('-----------------------------------------------------------------------')


# Function called when the player reaches the prisoner
def game_over():
    if item_count == 7:
        outcome = "win"
        show_game_over(outcome)
    else:
        outcome = "lost"
        show_game_over(outcome)
    exit(0)


# Main procedure for program
def main():
    colors()
    notification = ""
    current_room = "Garage"
    current_item = ""
    inventory = []
    first_run = True
    global item_count
    needs_collected = False

    # Function clears console screen
    def clear_screen(lines):
        clear = "\r" * lines
        print(clear)

    # Function gets players current inventory and returns as a string
    def show_inventory():
        if inventory:
            delim = ', '
            items = delim.join(inventory)
            print("Items in inventory: ({})".format(BOLD + INFO + items + RESET))
        else:
            print("No items in inventory")

    # Function shows if current room has item to be collected
    def show_needs_collected():
        if needs_collected:
            print("You see a {}, collect before moving on.".format(BOLD + SUCCESS + current_item + RESET))
        else:
            print("Item has been collected or no item in room")

    # Show instructions to player
    def show_instructions():
        error('-----------------------------------------------------------------------')
        error('                      Escaped Prisoner                                 ')
        error('-----------------------------------------------------------------------')
        print("Escaped Prisoner, don't get caught!!")
        print("Collect all 7 parts to the shotgun or be taken hostage by the prisoner")
        print("Four commands can be entered: ")
        print("   Move commands: go North, go South, go East, go West (case-sensitive)")
        print("   Get command: get item (no need to type the name, just the word item")
        print("   Help command: help (will display available commands")
        print("   Exit program: exit")
        info('------------------------------------------------------------------------')
        print("You are in the {}".format(BOLD + WARNING + current_room + RESET))
        show_inventory()
        info('------------------------------------------------------------------------')

    # Function provides game information
    def show_game_info():
        error('-----------------------------------------------------------------------')
        error('                      Escaped Prisoner                                 ')
        error('-----------------------------------------------------------------------')
        print("You are in the {}".format(BOLD + WARNING + current_room + RESET))
        show_inventory()
        show_needs_collected()
        error('-----------------------------------------------------------------------')

    # Function displays commands player can enter
    def show_commands():
        error('-----------------------------------------------------------------------')
        print("   Move commands: go North, go South, go East, go West (case-sensitive)")
        print("   Get command: get item (no need to type the name, just the word item")
        print("   Help command: help (will display available commands")
        print("   Exit program: exit")
        error('------------------------------------------------------------------------')

    # Function verifies direction entered is valid
    def check_direction(direction, room):
        this_room = rooms.get(room)
        if direction in this_room:
            return True
        else:
            return False

    # Function gets the next room
    def get_room(direction, room):
        this_room = rooms.get(room)
        next_room = this_room.get(direction)
        return next_room

    # Function moves to next room
    def move_player(direction, room):
        next_room = get_room(direction, room)
        next_item = get_item(next_room)
        return next_room, next_item

    # Next few functions are associated with items
    # Function gets the next item
    def get_item(room):
        this_room = rooms.get(room)
        item = this_room.get("Item")
        return item

    # Function to check item entered is valid
    def check_item(item):
        if item == "item":
            return True
        else:
            return False

    # Function to collect item and add to inventory
    def collect_item(item):
        global item_count
        if item not in inventory:
            inventory.append(item)
        item_count += 1

    # Function presents to player option to get uncollected item
    # moving to next room
    def verify_move_player(item):
        if needs_collected:
            warning("You haven't collected the item for this room.", "Warning")
            verify_move = input(INFO + "Would you like to collect this item first? (yes/no) \n" + RESET)
            if verify_move == "yes":
                collect_item(item)
                time.sleep(2)
            else:
                return

    # Show a message in the notification area
    def show_message(title, message, message_type):
        message_type(title, message)
        time.sleep(3)
        print("\r", end='\r')
        global notification
        notification = ''
        return

    # Declaring rooms array or dictionary
    rooms = {
        'Garage': {'West': 'Sitting Room'},
        'Sitting Room': {'South': 'Kitchen', 'West': 'Study', 'Item': 'Action'},
        'Study': {'South': 'Living Room', 'East': 'Sitting Room', 'Item': 'Shotguns For Dummies'},
        'Living Room': {'North': 'Study', 'East': 'Dining Room', 'South': 'Master Bedroom', 'Item': 'Stock'},
        'Master Bedroom': {'East': 'Master Bath', 'North': 'Living Room', 'Item': 'Receiver'},
        "Master Bath": {'North': 'Dining Room', 'West': 'Master Bedroom', 'Item': 'Barrel'},
        "Dining Room": {"North": 'Kitchen', 'West': 'Living Room', 'South': 'Master Bath', 'Item': 'Shotgun Shells'},
        'Kitchen': {'North': 'Sitting Room', 'South': 'Dining Room', 'East': 'Basement', 'Item': 'Parts'},
        'Basement': {'Item': 'Prisoner'}
    }

    while True:
        var = notification if notification else print('', end='')
        action = ""
        prop = ""
        if not first_run:
            clear_screen(20)
            show_game_info()
        else:
            show_instructions()
            first_run = False
            needs_collected = False
        clear_screen(5)
        commands = input(BOLD + INFO + "Enter a command!!\n" + RESET)
        user_input = commands.split()
        try:
            if user_input[0] == 'exit':
                print("Exiting Program..")
                exit()
            elif user_input[0] == "help":
                show_commands()
                time.sleep(3)
                continue
            elif len(user_input) != 2:
                show_game_info()
                notification = show_message("Invalid number of parameters entered", "Error:", error)
                continue
            elif user_input[0] != "help" and user_input[0] != "go" and user_input[0] != "get" and user_input[0] != "quit":
                show_game_info()
                notification = show_message("Invalid command entered", "Error:", error)
                continue
            action = user_input[0]
            prop = user_input[1]
            # Action is go
            if action == "go":
                # Check direction entered is valid
                if check_direction(prop, current_room):
                    verify_move_player(current_item)
                    current_room, current_item = move_player(prop, current_room)
                    needs_collected = True
                    notification = show_message("You entered into the {}".format(current_room), "Success:", success)
                    if current_room == "Basement":
                        clear_screen(20)
                        break
                else:
                    notification = show_message("{} isn't a valid direction, try again.".format(prop), "Error:", error)
            # Action is get
            elif action == "get":
                # Check the item entered is valid
                if check_item(prop):
                    collect_item(current_item)
                    needs_collected = False
                    notification = show_message(current_item + " has been added to your inventory!", "Success:",success)
                    current_item = ""
                else:
                    notification = show_message("Invalid command entered, try again", "Error:", error)
                    continue
        # An index error will not end the program, will show an error and continue running
        except IndexError:
            notification = show_message("Invalid number of arguments entered, try again", "Error:", error)
            continue

    # Function to determine if game win or lost and then end
    game_over()


if __name__ == '__main__':
    main()
