import math

def exception(text):
    print("[ERROR] " + text)
    input("[Press ENTER to close]")
    exit(1)

def degrees_to_radian(degree):
    return degree * math.pi / 180

# -------- INPUTS -------- #
angle_resolution_d = 5.625 # degrees

y_offset = -20 # offset for the bicycle to be more centered
x_offset = 0

screen_y_min = -120
screen_y_max = 120
screen_x_min = -120
screen_x_max = 120

start_pos_y = -1
start_pos_x = -1

bike_pos_y = 0
bike_pos_x = 0 # = (-6 * SF / MOVE_SPEED * DRAW_SPEED) <= draw and move speed of the bicycle drawing function
bike_offset_x = -30
bike_offset_y = 2 # Fix offset from anchor point 3 to the ground

# -------- INPUTS -------- #
try:
    angle_d = int(input("Angle of the level {0 - 89}: "))
except ValueError:
    exception("Invalid angle input")

if (angle_d > 89 or angle_d < 0):
    exception("Invalid angle")

# -------- CALCULATIONS -------- #
# calculate offsets
screen_y_min = screen_y_min
screen_y_max = screen_y_max
screen_x_min = screen_x_min
screen_x_max = screen_x_max

# calculate angle
level_angle_index = int(angle_d / angle_resolution_d)
level_angle_d = level_angle_index * angle_resolution_d
if level_angle_d != angle_d:
    print("\n[WARNING] Requested level angle was " + str(angle_d) + "° but the real angle is " + str(level_angle_d) + "° (" + hex(level_angle_index) + ") in vectrex!")

level_angle_r = degrees_to_radian(level_angle_d)

# calculate level start point
if level_angle_d < 45:
    start_pos_x = screen_x_min
    start_pos_y = int(math.tan(level_angle_r) * screen_x_min)

elif level_angle_d > 45: 
    start_pos_y = screen_y_min
    start_pos_x = int(screen_y_min / math.tan(level_angle_r))

else:
    start_pos_y = screen_y_min
    start_pos_x = screen_x_min

# calculate bicycle y position
bike_pos_x = bike_pos_x + bike_offset_x

if level_angle_d < 45:
    bike_pos_y = int(math.tan(level_angle_r) * bike_pos_x)
    bike_pos_y = bike_pos_y + round(math.cos(level_angle_r) * bike_offset_y) # calculate offset from anchor point to the ground

elif level_angle_d >= 45: 
    bike_pos_y = int(math.tan(level_angle_r) * bike_pos_x)
    bike_pos_x = bike_pos_x - round(math.sin(-level_angle_d) * bike_offset_y) # calculate offset from anchor point to the ground

# calculate level draw vector
x_length_2 = (0 - start_pos_x) * (0 - start_pos_x)
y_length_2 = (0 - start_pos_y) * (0 - start_pos_y)
draw_vector_length = int(math.sqrt(x_length_2 + y_length_2))

# calculate x and y of draw vector
draw_vector_y = round(math.sin(level_angle_r) * draw_vector_length)
draw_vector_x = round(math.cos(level_angle_r) * draw_vector_length)

# add offsets
start_pos_y = start_pos_y + y_offset
start_pos_x = start_pos_x + x_offset
bike_pos_y  = bike_pos_y + y_offset
bike_pos_x  = bike_pos_x + x_offset

if start_pos_x < screen_x_min:
    start_pos_x = screen_x_min

if start_pos_y < screen_y_min:
    start_pos_y = screen_y_min

print("-----------------------------")
#print("Start Position: (" + str(start_pos_x) + "|" + str(start_pos_y) + ")")
#print("Player Position: (" + str(bike_pos_x) + "|" + str(bike_pos_y) + ")")
#print("Player Angle: " + str(level_angle_d) + "° or " + hex(level_angle_index) + " in vectrex")
#print("Draw vector: (" + str(draw_vector_x) + "|" + str(draw_vector_y) + ")")
#print("Draw vector length: " + str(draw_vector_length * 2))
print("{" + str(start_pos_y) + "," + str(start_pos_x) + "," + str(draw_vector_y) + "," + str(draw_vector_x) + "," + str(bike_pos_y) + "," + str(bike_pos_x) + "," + str(level_angle_index) + " ...")

# -------- END -------- #
input("[Press ENTER to close]")
exit(0)