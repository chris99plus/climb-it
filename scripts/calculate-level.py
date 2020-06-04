import math

def exception(text):
    print("[ERROR] " + text)
    input("[Press ENTER to close]")
    exit(1)

def degrees_to_radian(degree):
    return degree * (math.pi / 180)

def radian_to_degrees(radian):
    return radian * (180 / math.pi)

# -------- INPUTS -------- #
angle_resolution_d = 5.625 # degrees
move_speed = 0x7f

DEFAULT_Y_OFFSET = -20
DEFAULT_X_OFFSET = 10
DEFAULT_BIKE_X_OFFSET = -100
DEFAULT_ENEMY_POSITION_COUNTS = 32

y_offset = DEFAULT_Y_OFFSET # offset for the bicycle to be more centered
x_offset = DEFAULT_X_OFFSET

screen_y_min = -120
screen_y_max = 120
screen_x_min = -120
screen_x_max = 120

terrain_draw_speed = abs(screen_x_min) + screen_x_max

start_pos_y = -1
start_pos_x = -1

bike_pos_y = 0
bike_pos_x = 0
bike_offset_x = DEFAULT_BIKE_X_OFFSET
bike_offset_y = 2 # Fix offset from anchor point 3 to the ground

# -------- INPUTS -------- #
try:
    angle_d = int(input("Angle of the level {0 to 89}: "))
except ValueError:
    exception("Invalid angle input")

if angle_d > 89 or angle_d < 0:
    exception("Invalid angle")

try:
    y_offset = int(input("Y offset {" + str(screen_y_min) + " to " + str(screen_y_max) + "} [" + str(DEFAULT_Y_OFFSET) + "]: "))
except ValueError:
    y_offset = DEFAULT_Y_OFFSET

if y_offset < screen_y_min or y_offset > screen_y_max:
    exception("Invalid y offset")

try:
    x_offset = int(input("X offset {" + str(screen_x_min) + " to " + str(screen_x_max) + "} [" + str(DEFAULT_X_OFFSET) + "]: "))
except ValueError:
    x_offset = DEFAULT_X_OFFSET

if x_offset < screen_x_min or x_offset > screen_x_max:
    exception("Invalid x offset")

try:
    bike_offset_x = int(input("Bike x offset {" + str(screen_x_min) + " to 0} [" + str(DEFAULT_BIKE_X_OFFSET) + "]: "))
except ValueError:
    bike_offset_x = DEFAULT_BIKE_X_OFFSET

if bike_offset_x < screen_x_min or bike_offset_x > 0:
    exception("Invalid bike x offset")

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
    exception("Not implemented yet (angle >= 45°)")
    #bike_pos_x = bike_pos_x + round(math.sin(-level_angle_d) * bike_offset_y) # calculate offset from anchor point to the ground


# calculate level draw vector
x_length_2 = (0 - start_pos_x) * (0 - start_pos_x)
y_length_2 = (0 - start_pos_y) * (0 - start_pos_y)
draw_vector_length = int(math.sqrt(x_length_2 + y_length_2))

# calculate x and y of draw vector
draw_vector_y = round(math.sin(level_angle_r) * draw_vector_length)
draw_vector_x = round(math.cos(level_angle_r) * draw_vector_length)

# calculate enemy start positions
enemy_start_y = round(start_pos_y + (draw_vector_y * (terrain_draw_speed / move_speed)))
enemy_start_x = round(start_pos_x + (draw_vector_x * (terrain_draw_speed / move_speed)))

# calculate enemy move points
enemy_move_positions_y = []
enemy_move_positions_x = []

x_section_length = (draw_vector_x * (terrain_draw_speed / move_speed)) / DEFAULT_ENEMY_POSITION_COUNTS

for i in range(0, DEFAULT_ENEMY_POSITION_COUNTS):
    enemy_move_positions_x.append(round(enemy_start_x - i * x_section_length))
    if level_angle_d < 45:
        enemy_move_positions_y.append(int(math.tan(level_angle_r) * enemy_move_positions_x[i]))
    else:
        exception("Not implemented yet")

# add offsets
start_pos_y = start_pos_y + y_offset
start_pos_x = start_pos_x + x_offset
bike_pos_y  = bike_pos_y + y_offset
bike_pos_x  = bike_pos_x + x_offset
enemy_start_y = enemy_start_y + y_offset
enemy_start_x = enemy_start_x + x_offset

if enemy_start_y > screen_y_max:
    enemy_start_y = screen_y_max

if enemy_start_x > screen_x_max:
    enemy_start_x = screen_x_max

if start_pos_x < screen_x_min:
    start_pos_x = screen_x_min

if start_pos_y < screen_y_min:
    start_pos_y = screen_y_min

for i in range(0, DEFAULT_ENEMY_POSITION_COUNTS):
    enemy_move_positions_x[i] = enemy_move_positions_x[i] + x_offset
    enemy_move_positions_y[i] = enemy_move_positions_y[i] + y_offset

# -------- OUTPUT -------- #
print("-----------------------------")
print("Move speeds: " + hex(move_speed))
print("Draw the terrain with a scaling factor of: " + hex(terrain_draw_speed))
print("Level informations array:")
print("\t{" + str(start_pos_y) + "," + str(start_pos_x) + "," + str(draw_vector_y) + "," + str(draw_vector_x) + "," + \
            str(bike_pos_y) + "," + str(bike_pos_x) + "," + str(level_angle_index) + "},")

print("Enemy poitions array")
print("\t{", end="")
for i in range(0, DEFAULT_ENEMY_POSITION_COUNTS):
    if i != 0:
        print(",", end="")
    print("{" + str(enemy_move_positions_y[i]) + "," + str(enemy_move_positions_x[i]) + "}", end="")
    if i == DEFAULT_ENEMY_POSITION_COUNTS-1:
        print("},")

# -------- END -------- #
input("[Press ENTER to close]")
exit(0)