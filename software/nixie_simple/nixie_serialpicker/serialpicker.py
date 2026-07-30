import serial

ser = serial.Serial('COM4', 9600)

while True:
    user_input = input(
        "\n"
        "Nixie Tube Controller\n"
        "  Enter a tube number and a digit/command, e.g. '1 7', '2 off', or '1 scroll'\n"
        "  Commands: off, scroll\n"
        "  Type 'exit' or 'quit' to exit the program\n"
        "> "
    ).strip().lower()
    if user_input in ['exit', 'quit']:
        ser.write(bytes([1,10]))  # Sends 10 to turn off the nixie tube
        ser.write(bytes([2,10]))  # Sends 10 to turn off the nixie tube
        break
    else:
        tube_num, cmd = user_input.split()[0:2]
        try:
            tube_num = int(tube_num)
        except ValueError:
            print("Invalid tube number. Please enter 1 or 2.")
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

            if tube_num not in [1, 2]:
                print("Please enter a valid tube number (1 or 2).")
            else:
                if 0 <= digit <= 9:
                    ser.write(bytes([tube_num, digit]))
                else:
                    print("Please enter a number between 0 and 9.")

    response = ser.read_all().decode('utf-8').strip()
    print(f"Response: {response}")
    # print(f"Response: {ser.readline().decode('utf-8').strip()}")
