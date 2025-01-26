fn=64;		// Resolution for circular shapes
$fn=fn;		// Set global resolution for circles

// Motor dimensions
motor_d=36;			// Motor diameter
motor_l=60;			// Motor length

// Plate parameters
plate_screw_d = 3;			// Diameter of plate screw holes
plate_screw_off = 25/2;		// Offset of screw holes from center
plate_gear_hole_d = 13.5;	// Diameter of gear hole
plate_gear_hole_l = 16;		// Depth of gear hole

// Bottom screw offsets
bottom_screw_1_gap_y = 20;
bottom_screw_2_gap_y = 15;
bottom_screw_1_gap_x = 4;
bottom_screw_2_gap_x = 37;

// Thickness parameters
plate_h=4;			// Plate thickness
bottom_t = 7;		// Bottom thickness
front_t = 3;		// Front thickness for casing walls

// Motor case calculations
motor_case_d = motor_d + front_t * 2;  // Outer diameter including front thickness

// Position offsets
motor_plate_y = 14;
motor_plate_x_off = 1;

// Subtracting inner components from the main shape
difference()
{
	translate([0,0,bottom_t])
	union()
	{
		// Add motor mounting plate
		translate([motor_l,motor_case_d/2,motor_case_d/2])
		rotate([0,90,0])
		plate(plate_h=plate_h);

		// Create the motor casing with subtractions for motor and cutouts
		difference()
		{
			motor_case();

			// Subtract space for motor inside the case
			translate([0,front_t,front_t])
			motor();

			// Create cutout section inside motor case
			translate([0,0,motor_case_d/2])
			cube([motor_l-18, motor_case_d, motor_case_d/2]);
		}

		// Bottom support base for the motor casing
		translate([0,0,-bottom_t])
		cube([motor_l+plate_h, motor_case_d, bottom_t]);
	}

	// Cutting out space for motor plate attachment
	translate([motor_l+motor_plate_x_off,0,0])
	cube([plate_h,motor_plate_y,motor_case_d+bottom_t]);

	// Add bottom screw holes (hidden in preview using #)
	translate([0,front_t,4])
	bottom_screws();
}

// Creates the outer motor case
module motor_case()
{
	translate([0,motor_case_d/2,motor_case_d/2])
	rotate([0,90,0])
	cylinder(d=motor_case_d, h=motor_l);

	// Subtract a slot for motor fitting
	difference()
	{
		cube([motor_l+plate_h, motor_case_d, motor_case_d/2]);
		translate([0,motor_case_d/2,motor_case_d/2])
		rotate([0,90,0])
		cylinder(d=motor_case_d, h=motor_l+plate_h);
	}
}

// Places screws at the bottom of the casing
module bottom_screws()
{
	translate([bottom_screw_1_gap_x, (motor_d-bottom_screw_1_gap_y)/2, 0])
	{
		screw();
		translate([0,bottom_screw_1_gap_y,0])
		screw();
	}

	translate([bottom_screw_2_gap_x, (motor_d-bottom_screw_2_gap_y)/2, 0])
	{
		screw();
		translate([0,bottom_screw_2_gap_y,0])
		screw();
	}
}

// Creates a screw with a head and shaft
module screw(d1=8, d2=5, l2=20, l1=50)
{
	cylinder(d=d1, h=l1, $fn=fn/4);  // Main screw body
	translate([0,0,-l2])
	cylinder(d=d2, h=l2, $fn=fn/4);  // Screw head
}

// Creates the motor shape inside the casing
module motor()
{
	translate([0,motor_d/2,motor_d/2])
	rotate([0,90,0])
	union()
	{
		cylinder(d=motor_d, h=motor_l);  // Main motor body
		cylinder(d=plate_gear_hole_d, h=motor_l+plate_gear_hole_l);  // Gear shaft
	}
}

// Creates the motor mounting plate with screw holes
module plate(plate_h=1.5)
{
	rotate([0,0,180])
	difference()
	{
		linear_extrude(height = plate_h)
		difference()
		{
			circle(d=motor_case_d);       // Outer plate diameter
			circle(d=plate_gear_hole_d);   // Gear hole cutout

			// Screw holes at each quadrant of the plate
			translate([plate_screw_off,0,0])
			circle(d=plate_screw_d,$fn=fn/8);

			translate([-plate_screw_off,0,0])
			circle(d=plate_screw_d,$fn=fn/8);

			translate([0,plate_screw_off,0])
			circle(d=plate_screw_d,$fn=fn/8);

			translate([0,-plate_screw_off,0])
			circle(d=plate_screw_d,$fn=fn/8);
		}
	}
}
