include <../main.scad>

angle = 30;

color("green")
	part2();

translate([0, 0, -h])
rotate([angle, 0, 0])
	part3();	