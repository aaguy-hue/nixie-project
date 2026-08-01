import serial

ser = serial.Serial('COM4', 9600)

while True:
    user_input = input(
        "\n"
        "Nixie Tube Controller\n"
        "  Enter a tube number and a digit/command, e.g. '1 7', '2 off', or '1 scroll'\n"
        "  Commands: off, scroll\n"
        "  Type four numbers separated by spaces to set all four tubes at once, e.g. '1 2 3 4'\n"
        "  Type 'exit' or 'quit' to exit the program\n"
        "> "
    ).strip().lower()
    if user_input in ['exit', 'quit']:
        ser.write(bytes([1,10]))  # Sends 10 to turn off the nixie tube
        ser.write(bytes([2,10]))  # Sends 10 to turn off the nixie tube
        break
    elif len(user_input.split()) == 4:
        try:
            tube1, tube2, tube3, tube4 = map(int, user_input.split())
        except ValueError:
            print("Invalid input. Please enter four numbers between 0 and 9.")
            continue

        if all(0 <= tube <= 9 for tube in (tube1, tube2, tube3, tube4)):
            ser.write(bytes([1, tube1]))
            ser.write(bytes([2, tube2]))
            ser.write(bytes([3, tube3]))
            ser.write(bytes([4, tube4]))
        else:
            print("Please enter numbers between 0 and 9 for all four tubes.")
    else:
        tube_num, cmd = user_input.split()[0:2]
        try:
            tube_num = int(tube_num)
        except ValueError:
            print("Invalid tube number. Please enter a number between 1 and 4.")
            continue
        if cmd == 'off':
            ser.write(bytes([tube_num, 10]))
        elif cmd == 'scroll':
            ser.write(bytes([tube_num, 16]))
        else:
            try:
                digit = int(cmd)
            except ValueError:
                print("Invalid digit. Please enter a number between 0 and 9.")
                continue


            if tube_num not in range(1, 5):
                print("Please enter a valid tube number (1-4).")
            else:
                if 0 <= digit <= 9:
                    ser.write(bytes([tube_num, digit]))
                else:
                    print("Please enter a number between 0 and 9.")

    response = ser.read_all().decode('utf-8').strip()
    print(f"Response: {response}")
    # print(f"Response: {ser.readline().decode('utf-8').strip()}")
