-- Ada_P2 --

with Ada.Text_IO;                         use Ada.Text_IO;
with Ada.Integer_Text_IO;                 use Ada.Integer_Text_IO; 
with Ada.Float_Text_IO;                   use Ada.Float_Text_IO; 

procedure Fail is
   
   -- Deluppgift_1 --
   
   function Deluppgift_1 (I: in Integer) return Float is
      
      Product: Float;
      
   begin     
      
      Product := Float'Rounding(Float(I) * 32.7);
      
      return Product;     
      
   end Deluppgift_1;  
   
   -- Deluppgift_2 --
   
   function "-" (Left: in Character;
		 Right: in Float) return Float is
      
      Diff: Float;
      
   begin
      
      Diff := Float'Ceiling(Float'Value(Left'Image(2..2)) - Right);
      
      return Diff;
      
   end "-";      
   
   -- Deluppgift_3 --
   
   procedure Deluppgift_3 (I: out Integer;
			   Sum: out Integer) is  
   begin
      
      Put("Mata in ett heltal: ");
      Get(I);
      
      Sum := Integer(Float(I) + 32.7);
      
   end Deluppgift_3;   
   
   -- Huvudprogram --
   
   I, Sum: Integer;
   F: Float;
   C: Character;
      
begin
   
   -- Deluppgift_1 --
   
   Put("Mata in ett heltal: ");
   Get(I);
   Put("produkten av ");
   Put(I, Width => 0);
   Put(" och 32.7 blir ");
   Put(Deluppgift_1(I), Fore => 0, Aft => 1, Exp => 0);
   New_Line(2);
   
   -- Deluppgift_2 --
   
   Put("Mata in ett tecken: ");
   Get(C);
   Put("Mata in ett flyttal: ");
   Get(F);
   
   Put("Den beräknade differensen mellan " & C & " och ");
   Put(F, Fore => 0, Aft => 1, Exp => 0);
   Put(" blir ");
   Put(C - F, Fore => 0, Aft => 1, Exp => 0);
   New_Line(2);
   
   -- Deluppgift_3 --
   
   Deluppgift_3(I, Sum);
   Put("summan av ");
   Put(I, Width => 0);
   Put(" och 32.7 blir ");
   Put(Sum, Width => 0);
   
end Fail;
