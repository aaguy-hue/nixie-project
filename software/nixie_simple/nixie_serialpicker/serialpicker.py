import serial

ser = serial.Serial('COM4', 9600)

while True:
    user_input = input("Enter a number (0-9), 'off' to turn off the nixie tube, 'scroll' to enable scrolling, or 'exit' to quit: ")
    if user_input.lower() in ['exit', 'quit']:
        ser.write(bytes([10]))  # Sends 10 to turn off the nixie tube
        break
    elif user_input.lower() == 'off':
        ser.write(bytes([10]))  # Sends 10 to turn off the nixie tube
    elif user_input.lower() == 'scroll':
        ser.write(bytes([16]))  # Sends 16 to enable scrolling animation
    else:
        try:
            num = int(user_input)
            if 0 <= num <= 9:
                ser.write(bytes([num]))  # Sends the number as a single byte
            else:
                print("Please enter a number between 0 and 9.")
        except ValueError:
            print("Invalid input. Please enter a valid number.")

    if (ser.in_waiting > 0):
        response = ser.readline().decode('utf-8').strip()
        print(f"Response: {response}")
    # print(f"Response: {ser.readline().decode('utf-8').strip()}")
