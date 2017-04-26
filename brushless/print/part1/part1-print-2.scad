include <../../parts/part1.scad>
use <part1-print.scad>

rotate([-90, 0, 0])
difference() {
	union()
	{
		difference()
		{
			part1();
			cutA();
		}
		
		intersection()
		{
			part1Base();
			boltsBplus();

		}
	}
	boltsBminus();
}