import serial

ser = serial.Serial('COM4', 9600)

while True:
    user_input = input(
        "Nixie Tube Controller\n"
        "  Enter a tube number and digit, e.g. '1 7'\n"
        "  Commands: off, scroll, exit\n"
        "> "
    ).strip().lower()
    if user_input in ['exit', 'quit']:
        ser.write(bytes([10]))  # Sends 10 to turn off the nixie tube
        break
    elif user_input == 'off':
        ser.write(bytes([10]))  # Sends 10 to turn off the nixie tube
    elif user_input == 'scroll':
        ser.write(bytes([16]))  # Sends 16 to enable scrolling animation
    else:
        try:
            tube_num, digit = map(int, user_input.split())
            if tube_num not in [1, 2]:
                print("Please enter a valid tube number (1 or 2).")
            else:
                if 0 <= digit <= 9:
                    ser.write(bytes([tube_num, digit]))
                else:
                    print("Please enter a number between 0 and 9.")
        except ValueError:
            print("Invalid input. Please enter a valid number.")

    response = ser.read_all().decode('utf-8').strip()
    print(f"Response: {response}")
    # print(f"Response: {ser.readline().decode('utf-8').strip()}")
