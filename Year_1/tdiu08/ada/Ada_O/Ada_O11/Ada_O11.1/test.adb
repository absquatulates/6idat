-- Ada.011.1 --
-- hugho678: Samarbetat med carbj841, Carl Björlin, samma program

with Ada.Text_IO;                                 use Ada.Text_IO;
with Ada.Integer_Text_IO;                         use Ada.Integer_Text_IO;
with Ada.FLoat_Text_IO;                           use Ada.FLoat_Text_IO; 
with Ada.Numerics.Elementary_Functions;           use Ada.Numerics.Elementary_Functions;
with Ada.Numerics;                                use Ada.Numerics;

procedure Test is
   
   
   -- Menu_Selection
   
   procedure Menu_Selection (Selection: in out Integer) is
   
   begin
   
   Put_Line("=== HUVUDMENY ===");
   Put_Line("1. Beräkna hypotenusa");
   Put_Line("2. Beräkna triangelvinklar");
   Put_Line("3. Beräkna N-fakultet");
   Put_Line("4. Avsluta programmet");
   
   loop
      Put("Val: ");
      Get(Selection);
      
      exit when Selection <= 4 and Selection >= 1;
      
      Put_Line("Felaktigt val!");
      
   end loop;  
   
   end Menu_Selection;
   
   
   ---------- HYPOTHENUSE ----------
   
   -- Calculate_Hypothenuse
   
   function Calculate_Hypothenuse (Katet1, Katet2: in Integer) return Float is
      
      Hypothenuse: Float;
      K1, K2: Float;
      
   begin
      
     K1 := Float(Katet1);
     K2 := Float(Katet2);
            
      
     Hypothenuse := Sqrt((K1*K1)+(K2*K2));
      
     return Hypothenuse;
      
   end Calculate_Hypothenuse;
   
   -- Hypothenuse_Program
   
   procedure Hypothenuse_Program is
      
      Katet1, Katet2: Integer;
      H: Float;
      
   begin   
      loop
	 
	 Put("Mata in kateternas längder: ");
	 Get(Katet1);
	 Get(Katet2);
	 
	 exit when Katet1 > 0 and Katet2 > 0;
	 
	 Put_Line("Felaktigt val!");
	 
      end loop; 
      
	H :=  Calculate_Hypothenuse(Katet1, Katet2);
           
	Put("Hypotenusan är ");
	Put(H, 0, 2, 0);
	New_Line(2);
            
   end Hypothenuse_Program;  
   
   
   ---------- ANGLES ----------
   
   -- Calculate_Angles
   
   procedure Calculate_Angles (Hc, Sa: in Float; Va, Vb, Vc: out Float) is      
      
   begin
      
      Va:= arcsin(Sa/Hc, 360.0);
      
      Vc:= 90.0;
      
      Vb:= 180.0 - Va - Vc;
      
   end Calculate_Angles;   
      
   -- Angle_Program
   
   procedure Angle_Program is
      
      Hc, Sa: Float;
      Va, Vb, Vc: Float;
      
   begin
      
      loop
      
	 Put("Mata in hypotenusans längd: ");
	 Get(Hc);
      
	 Put("Mata in vertikala katetens längd: ");
	 Get(Sa);
	 
	 exit when Sa > 0.0 and Hc > Sa;
	 
	 Put("Felaktigt val!");
	 
      end loop;   
      
      Calculate_Angles(Hc, Sa, Va, Vb, Vc);
      
      Put("Va: ");
      Put(Va, 0, 1, 0);
      Put(" grader");
      New_Line;
      Put("Vb: ");
      Put(Vb, 0, 1, 0);
      Put(" grader");
      New_Line;
      Put("Vc: ");
      Put(Vc, 0, 1, 0);
      Put(" grader");
      New_Line(2);
      
   end Angle_Program;   
   
   
   ---------- FACTORIAL ----------
   
     -- Calculate_Factorial
   
   function Calculate_Factorial(N: in Integer) return Integer is
      
      M: Integer;
      
   begin
      
      M:=N;
      
      for I in Integer range 1..(M-1) loop
	 M := M*I;
	 
      end loop;               
      
      return M;
      
   end Calculate_Factorial;
   
   -- Factorial_Program
   
   procedure Factorial_Program is
      
      N: Integer;
      M: Integer;
      
   begin
      
      loop
	 Put("Mata in N: ");
	 Get(N);
	 
	 exit when N >= 0;
	 
	 Put("Felaktigt val!");
	 
      end loop;
      
      if N = 0 then
	 M := 1;
      else      
	 M:= Calculate_Factorial(N);	 
      end if;
      
      Put(N, 1);
      Put("-fakultet = ");
      Put(M, 1); 
      New_Line(2);
            
   end Factorial_Program;       

   ---------- HUVUDPROGRAM ----------
   
   -- Deklarationer Huvudprogram
   
   Selection: Integer;
   
begin
   
   Selection := 0;
   
   Put_Line("Välkommen till miniräknaren!");
   
   loop
      Menu_Selection(Selection);
      
      
      if Selection = 1 then
	  Hypothenuse_Program;
      end if;
      
      if Selection = 2 then
	  Angle_Program;
      end if;
      
      if Selection = 3 then
	  Factorial_Program;
      end if;
      
      exit when Selection  = 4;
      
   end loop;
   
   Put("Ha en bra dag!");
   
   
   
end Test;
