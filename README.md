Cool Compiler
=============

Just your nancy pancy learning tool here. I'm learning about compilers and taking a class on
Coursera.

As a note, when I started this project I was using c++ < c++11, so I couldn't use the nice
`enum class { ... }` definitions. Unfortunately this means I had to use a hack if I wanted 
that functionality (which I did). I originally got the idea from [this site](http://bourt.com/blog/?p=372)
```
struct Join {
	enum E {
		Miter,
		Bevel,
		Round
	} e;
	Join(E e) : e(e) {}
	operator E() { return e; }
}
```

Hand Written
============
I understand hand-writing things are usually not the way to program, however I am 
learning so it's all good. After reading [this overview on Bison's tables](http://www.cs.uic.edu/~spopuri/cparser.html),
I realized that to keep going on the route I'm traveling down I would have to optimize all these tables
and pretty much create a mini-Bison. So....nah. I think I got the gist.