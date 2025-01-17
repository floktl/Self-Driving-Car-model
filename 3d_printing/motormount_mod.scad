$fn=64;

module all(){
  difference() {
    translate([0,-18,0])
    import_stl("motormount_v2_with_holes.stl");

    #translate([31,-50,-25])
    cube([10,100,100]);
  }
}

all();
#plate();
module plate(){
  plate_h=1.5;
  screw_d=3;
  screw_off=25/2;
  motor_d=36;
  translate([-29,0,18.5])
  rotate([0,-90,0])
  linear_extrude(height = plate_h) 
  difference(){
    circle(d=motor_d+5.5);
    circle(d=13.5);

    translate([screw_off,0,0])
    circle(d=screw_d);

    translate([-screw_off,0,0])
    circle(d=screw_d);

    translate([0,screw_off,0])
    circle(d=screw_d);

    translate([0,-screw_off,0])
    circle(d=screw_d);
  }

}