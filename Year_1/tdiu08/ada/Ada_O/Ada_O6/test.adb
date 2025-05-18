-- Ada_O6 --
-- hugho678: Samarbetat med carbj841, Carl Björlin, samma program

with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Test is
   
   function  Fib (N : in Positive) 
		 return Positive is
      
   begin
      
      if N = 1 or N = 2 then
	 return 1;
      end if;

	 return Fib(N-1) + Fib(N-2);
     
   end Fib;
   
   function Hojd (H : in Positive) return Natural is
      
   begin
      
      if H = 1 then
	 return 0;
      elsif H = 2 then
	 return 1;
      end if;
      
      return (H-1)*((H-2)*2+1)+Hojd(H-1);
      
   end Hojd;
   
   N, H : Positive;
   
begin
     
     Put("Mata in N och H: ");
     Get(N);
     Get(H);
     Skip_Line;
     
     Put("Fibonacci-tal nummer ");
     Put(N, 0);
     Put(" är ");
     Put(Fib(N), 0);
     Put_Line(".");
     
     Put("Det behövs ");
     Put(Hojd(H),0);
     Put(" stenar för att bygga trappan."); 
	   
	   
end Test;

