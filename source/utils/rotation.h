// ***************************************************************************
// rotation
// ***************************************************************************

#pragma once

// ---------------------------------------------------------------------------
// macros for compile time rotation computation

// ---------------------------------------------------------------------------
// sin table

#define sin_0   0
#define sin_1   0.0980171
#define sin_2   0.19509
#define sin_3   0.290285
#define sin_4   0.382683
#define sin_5   0.471397
#define sin_6   0.55557
#define sin_7   0.634393
#define sin_8   0.707107
#define sin_9   0.77301
#define sin_10  0.83147
#define sin_11  0.881921
#define sin_12  0.92388
#define sin_13  0.95694
#define sin_14  0.980785
#define sin_15  0.995185
#define sin_16  1
#define sin_17  sin_15
#define sin_18  sin_14
#define sin_19  sin_13
#define sin_20  sin_12
#define sin_21  sin_11
#define sin_22  sin_10
#define sin_23  sin_9
#define sin_24  sin_8
#define sin_25  sin_7
#define sin_26  sin_6
#define sin_27  sin_5
#define sin_28  sin_4
#define sin_29  sin_3
#define sin_30  sin_2
#define sin_31  sin_1
#define sin_32  sin_0
#define sin_33  -sin_1
#define sin_34  -sin_2
#define sin_35  -sin_3
#define sin_36  -sin_4
#define sin_37  -sin_5
#define sin_38  -sin_6
#define sin_39  -sin_7
#define sin_40  -sin_8
#define sin_41  -sin_9
#define sin_42  -sin_10
#define sin_43  -sin_11
#define sin_44  -sin_12
#define sin_45  -sin_13
#define sin_46  -sin_14
#define sin_47  -sin_15
#define sin_48  -sin_16
#define sin_49  -sin_17
#define sin_50  -sin_18
#define sin_51  -sin_19
#define sin_52  -sin_20
#define sin_53  -sin_21
#define sin_54  -sin_22
#define sin_55  -sin_23
#define sin_56  -sin_24
#define sin_57  -sin_25
#define sin_58  -sin_26
#define sin_59  -sin_27
#define sin_60  -sin_28
#define sin_61  -sin_29
#define sin_62  -sin_30
#define sin_63  -sin_31

// ---------------------------------------------------------------------------
// cos table

#define cos_0   sin_16
#define cos_1   sin_17
#define cos_2   sin_18
#define cos_3   sin_19
#define cos_4   sin_20
#define cos_5   sin_21
#define cos_6   sin_22
#define cos_7   sin_23
#define cos_8   sin_24
#define cos_9   sin_25
#define cos_10  sin_26
#define cos_11  sin_27
#define cos_12  sin_28
#define cos_13  sin_29
#define cos_14  sin_30
#define cos_15  sin_31
#define cos_16  sin_32
#define cos_17  sin_33
#define cos_18  sin_34
#define cos_19  sin_35
#define cos_20  sin_36
#define cos_21  sin_37
#define cos_22  sin_38
#define cos_23  sin_39
#define cos_24  sin_40
#define cos_25  sin_41
#define cos_26  sin_42
#define cos_27  sin_43
#define cos_28  sin_44
#define cos_29  sin_45
#define cos_30  sin_46
#define cos_31  sin_47
#define cos_32  sin_48
#define cos_33  sin_49
#define cos_34  sin_50
#define cos_35  sin_51
#define cos_36  sin_52
#define cos_37  sin_53
#define cos_38  sin_54
#define cos_39  sin_55
#define cos_40  sin_56
#define cos_41  sin_57
#define cos_42  sin_58
#define cos_43  sin_59
#define cos_44  sin_60
#define cos_45  sin_61
#define cos_46  sin_62
#define cos_47  sin_63
#define cos_48  sin_0
#define cos_49  sin_1
#define cos_50  sin_2
#define cos_51  sin_3
#define cos_52  sin_4
#define cos_53  sin_5
#define cos_54  sin_6
#define cos_55  sin_7
#define cos_56  sin_8
#define cos_57  sin_9
#define cos_58  sin_10
#define cos_59  sin_11
#define cos_60  sin_12
#define cos_61  sin_13
#define cos_62  sin_14
#define cos_63  sin_15

// ---------------------------------------------------------------------------
// rotate single vector
// compute values const double and exploit constant propagation
// casting to long int causes overflow errors to show up when data
// is actually stored as int

#define rotate_vector(angle, y, x) \
{ \
(long int)(((double) y) * cos_##angle + ((double) x) * sin_##angle), \
(long int)(((double) x) * cos_##angle - ((double) y) * sin_##angle) \
},

// ---------------------------------------------------------------------------
// rotate single vector with offsets

#define rotate_move_vector(angle, y, x, dy, dx) \
{ \
(long int)(((double) y) * cos_##angle + ((double) x) * sin_##angle) + dy, \
(long int)(((double) x) * cos_##angle - ((double) y) * sin_##angle) + dx \
},

// ---------------------------------------------------------------------------
// rotate vector list

#define rotate_vector_list_1(angle, y, x) \
rotate_vector(angle, y, x)

#define rotate_vector_list_2(angle, y, x, rest...) \
rotate_vector(angle, y, x) \
rotate_vector_list_1(angle, rest)

#define rotate_vector_list_3(angle, y, x, rest...) \
rotate_vector(angle, y, x) \
rotate_vector_list_2(angle, rest)

#define rotate_vector_list_4(angle, y, x, rest...) \
rotate_vector(angle, y, x) \
rotate_vector_list_3(angle, rest)

#define rotate_vector_list_5(angle, y, x, rest...) \
rotate_vector(angle, y, x) \
rotate_vector_list_4(angle, rest)

#define rotate_vector_list_6(angle, y, x, rest...) \
rotate_vector(angle, y, x) \
rotate_vector_list_5(angle, rest)

#define rotate_vector_list_7(angle, y, x, rest...) \
rotate_vector(angle, y, x) \
rotate_vector_list_6(angle, rest)

#define rotate_vector_list_8(angle, y, x, rest...) \
rotate_vector(angle, y, x) \
rotate_vector_list_7(angle, rest)

#define rotate_vector_list_9(angle, y, x, rest...) \
rotate_vector(angle, y, x) \
rotate_vector_list_8(angle, rest)

#define rotate_vector_list_10(angle, y, x, rest...) \
rotate_vector(angle, y, x) \
rotate_vector_list_9(angle, rest)

#define rotate_vector_list_11(angle, y, x, rest...) \
rotate_vector(angle, y, x) \
rotate_vector_list_10(angle, rest)

#define rotate_vector_list_12(angle, y, x, rest...) \
rotate_vector(angle, y, x) \
rotate_vector_list_11(angle, rest)

#define rotate_vector_list_13(angle, y, x, rest...) \
rotate_vector(angle, y, x) \
rotate_vector_list_12(angle, rest)

#define rotate_vector_list(angle, size, vectors...) \
{ \
rotate_vector_list_##size(angle, vectors) \
}

// ---------------------------------------------------------------------------
// rotate single packet

#define rotate_packet(angle, mode, y, x) \
{ \
mode, \
(int)(((double) y) * cos_#angle + ((double) x) * sin_##angle), \
(int)(((double) x) * cos_#angle - ((double) y) * sin_##angle) \
},

// ---------------------------------------------------------------------------
// rotate packet list

#define rotate_packet_list_1(angle, y, x) \
rotate_packet(angle, mode, y, x)

#define rotate_packet_list_2(angle, y, x, rest...) \
rotate_packet(angle, y, x) \
rotate_packet_list_1(angle, rest)

#define rotate_packet_list_3(angle, y, x, rest...) \
rotate_packet(angle, y, x) \
rotate_packet_list_2(angle, rest)

#define rotate_packet_list_4(angle, y, x, rest...) \
rotate_packet(angle, y, x) \
rotate_packet_list_3(angle, rest)

#define rotate_packet_list_5(angle, y, x, rest...) \
rotate_packet(angle, y, x) \
rotate_packet_list_4(angle, rest)

#define rotate_packet_list_6(angle, y, x, rest...) \
rotate_packet(angle, y, x) \
rotate_packet_list_5(angle, rest)

#define rotate_packet_list_7(angle, y, x, rest...) \
rotate_packet(angle, y, x) \
rotate_packet_list_6(angle, rest)

#define rotate_packet_list_8(angle, y, x, rest...) \
rotate_packet(angle, y, x) \
rotate_packet_list_7(angle, rest)

#define rotate_packet_list_9(angle, y, x, rest...) \
rotate_packet(angle, y, x) \
rotate_packet_list_8(angle, rest)

#define rotate_packet_list_10(angle, y, x, rest...) \
rotate_packet(angle, y, x) \
rotate_packet_list_9(angle, rest)

#define rotate_packet_list(angle, size, vectors...) \
rotate_packet_list_##size##(angle, vectors)

// --------------------------------------------------------------------------

#define rotation_table_entry(angle, name, size, vectors...) \
const struct vector_t const name##_##angle[] = rotate_vector_list(angle, size, vectors);

#define rotation_table(name, size, vectors...) \
rotation_table_entry(0, name, size, vectors) \
rotation_table_entry(1, name, size, vectors) \
rotation_table_entry(2, name, size, vectors) \
rotation_table_entry(3, name, size, vectors) \
rotation_table_entry(4, name, size, vectors) \
rotation_table_entry(5, name, size, vectors) \
rotation_table_entry(6, name, size, vectors) \
rotation_table_entry(7, name, size, vectors) \
rotation_table_entry(8, name, size, vectors) \
rotation_table_entry(9, name, size, vectors) \
rotation_table_entry(10, name, size, vectors) \
rotation_table_entry(11, name, size, vectors) \
rotation_table_entry(12, name, size, vectors) \
rotation_table_entry(13, name, size, vectors) \
rotation_table_entry(14, name, size, vectors) \
rotation_table_entry(15, name, size, vectors) \
rotation_table_entry(16, name, size, vectors) \
rotation_table_entry(17, name, size, vectors) \
rotation_table_entry(18, name, size, vectors) \
rotation_table_entry(19, name, size, vectors) \
rotation_table_entry(20, name, size, vectors) \
rotation_table_entry(21, name, size, vectors) \
rotation_table_entry(22, name, size, vectors) \
rotation_table_entry(23, name, size, vectors) \
rotation_table_entry(24, name, size, vectors) \
rotation_table_entry(25, name, size, vectors) \
rotation_table_entry(26, name, size, vectors) \
rotation_table_entry(27, name, size, vectors) \
rotation_table_entry(28, name, size, vectors) \
rotation_table_entry(29, name, size, vectors) \
rotation_table_entry(30, name, size, vectors) \
rotation_table_entry(31, name, size, vectors) \
rotation_table_entry(32, name, size, vectors) \
rotation_table_entry(33, name, size, vectors) \
rotation_table_entry(34, name, size, vectors) \
rotation_table_entry(35, name, size, vectors) \
rotation_table_entry(36, name, size, vectors) \
rotation_table_entry(37, name, size, vectors) \
rotation_table_entry(38, name, size, vectors) \
rotation_table_entry(39, name, size, vectors) \
rotation_table_entry(40, name, size, vectors) \
rotation_table_entry(41, name, size, vectors) \
rotation_table_entry(42, name, size, vectors) \
rotation_table_entry(43, name, size, vectors) \
rotation_table_entry(44, name, size, vectors) \
rotation_table_entry(45, name, size, vectors) \
rotation_table_entry(46, name, size, vectors) \
rotation_table_entry(47, name, size, vectors) \
rotation_table_entry(48, name, size, vectors) \
rotation_table_entry(49, name, size, vectors) \
rotation_table_entry(50, name, size, vectors) \
rotation_table_entry(51, name, size, vectors) \
rotation_table_entry(52, name, size, vectors) \
rotation_table_entry(53, name, size, vectors) \
rotation_table_entry(54, name, size, vectors) \
rotation_table_entry(55, name, size, vectors) \
rotation_table_entry(56, name, size, vectors) \
rotation_table_entry(57, name, size, vectors) \
rotation_table_entry(58, name, size, vectors) \
rotation_table_entry(59, name, size, vectors) \
rotation_table_entry(60, name, size, vectors) \
rotation_table_entry(61, name, size, vectors) \
rotation_table_entry(62, name, size, vectors) \
rotation_table_entry(63, name, size, vectors) \
const struct vector_t* const name[] = \
{ \
name##_0, name##_1, name##_2, name##_3, name##_4, name##_5, name##_6, name##_7, name##_8, name##_9, \
name##_10, name##_11, name##_12, name##_13, name##_14, name##_15, name##_16, name##_17, name##_18, name##_19, \
name##_20, name##_21, name##_22, name##_23, name##_24, name##_25, name##_26, name##_27, name##_28, name##_29, \
name##_30, name##_31, name##_32, name##_33, name##_34, name##_35, name##_36, name##_37, name##_38, name##_39, \
name##_40, name##_41, name##_42, name##_43, name##_44, name##_45, name##_46, name##_47, name##_48, name##_49, \
name##_50, name##_51, name##_52, name##_53, name##_54, name##_55, name##_56, name##_57, name##_58, name##_59, \
name##_60, name##_61, name##_62, name##_63, \
};

//&name##_1, &##name##_2, &##name##_3, &##name##_4, &##name##_5, &##name##_6, &##name##_7, &##name##_8, &##name##_9, 

// ---------------------------------------------------------------------------
#if 0
#define rotate_vectorlist(angle, y0, x0, y1, x1, y2, x2, y3, x3, y4, x4, y5, x5, y6, x6, y7, x7, y8, x8) \
	rotate_vector(y0, x0, angle), \
	rotate_vector(y1, x1, angle), \
	rotate_vector(y2, x2, angle), \
	rotate_vector(y3, x3, angle), \
	rotate_vector(y4, x4, angle), \
	rotate_vector(y5, x5, angle), \
	rotate_vector(y6, x6, angle), \
	rotate_vector(y7, x7, angle), \
	rotate_vector(y8, x8, angle) \

#define genship(name, angle, vectorlist...) \
const struct sprite_vector const vectors_##name##angle[] = \
{ \
rotate_vectorlist(angle, vectorlist) \
}; \
const struct sprite_shape shape_##name##angle = \
{ \
	TYPE_DUFFY, \
	VECTOR_LIST(vectors_##name##angle) \
}; \

#define genships(name, vectorlist...) \
genship(name, 0, vectorlist) \
genship(name, 2, vectorlist) \
genship(name, 4, vectorlist) \
genship(name, 6, vectorlist) \
genship(name, 8, vectorlist) \
genship(name, 10, vectorlist) \
genship(name, 12, vectorlist) \
genship(name, 14, vectorlist) \
genship(name, 16, vectorlist) \
genship(name, 18, vectorlist) \
genship(name, 20, vectorlist) \
genship(name, 22, vectorlist) \
genship(name, 24, vectorlist) \
genship(name, 26, vectorlist) \
genship(name, 28, vectorlist) \
genship(name, 30, vectorlist) \
genship(name, 32, vectorlist) \
genship(name, 34, vectorlist) \
genship(name, 36, vectorlist) \
genship(name, 38, vectorlist) \
genship(name, 40, vectorlist) \
genship(name, 42, vectorlist) \
genship(name, 44, vectorlist) \
genship(name, 46, vectorlist) \
genship(name, 48, vectorlist) \
genship(name, 50, vectorlist) \
genship(name, 52, vectorlist) \
genship(name, 54, vectorlist) \
genship(name, 56, vectorlist) \
genship(name, 58, vectorlist) \
genship(name, 60, vectorlist) \
genship(name, 62, vectorlist) \
const struct sprite_shape* const name##_shapes[] = \
{ \
	&shape_##name##0, \
	&shape_##name##2, \
	&shape_##name##4, \
	&shape_##name##6, \
	&shape_##name##8, \
	&shape_##name##10, \
	&shape_##name##12, \
	&shape_##name##14, \
	&shape_##name##16, \
	&shape_##name##18, \
	&shape_##name##20, \
	&shape_##name##22, \
	&shape_##name##24, \
	&shape_##name##26, \
	&shape_##name##28, \
	&shape_##name##30, \
	&shape_##name##32, \
	&shape_##name##34, \
	&shape_##name##36, \
	&shape_##name##38, \
	&shape_##name##40, \
	&shape_##name##42, \
	&shape_##name##44, \
	&shape_##name##46, \
	&shape_##name##48, \
	&shape_##name##50, \
	&shape_##name##52, \
	&shape_##name##54, \
	&shape_##name##56, \
	&shape_##name##58, \
	&shape_##name##60, \
	&shape_##name##62 \
}; 

#endif

// ***************************************************************************
// end of file rotation.h
// ***************************************************************************
