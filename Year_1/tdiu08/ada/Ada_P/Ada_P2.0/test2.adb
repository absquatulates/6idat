-- Ada_P2.0 --

with Ada.Text_IO;                         use Ada.Text_IO;
with Ada.Integer_Text_IO;                 use Ada.Integer_Text_IO; 
with Ada.Float_Text_IO;                   use Ada.Float_Text_IO; 


procedure Test2 is   
   
   -- Deluppgift_1 --
   
   function Deluppgift_1 (R: in Float) return Integer is
      
      Area: Integer;
      
   begin
      
      Area := Integer(Float'Ceiling(Float(R) * Float(R) * 3.14));
      
      return Area;
      
   end Deluppgift_1;
   
   -- Deluppgift_2 --
   
   function "/" (Left: in Float;
		 Right: in Character) return Integer is
      
      Kvot: Integer;
      
   begin
      
      Kvot := Integer(Float'Floor(Left / Float'Value(Right'Image(2..2))));
      
      return Kvot;
      
   end "/";
   
   -- Deluppgift_3 --
   
   procedure Deluppgift_3 (S: out String;
			   F: out Float;
			   Product: out Float) is
      
   begin
      
      Put("Mata in en sträng med exakt 3 tecken: ");
      Get(S);
      Put("Mata in ett flyttal: ");
      Get(F);
      
      Product := Float'Value(S) * F;
      
   end Deluppgift_3;  
   
   -- Huvudprogram --
   
   R, F, Product: Float;
   C: Character;
   S: String(1..3);
   
begin
   
   -- Deluppgift_1 --
   
   Put("Mata in längden: ");
   Get(R);
   
   Put("Den beräknade arean blev: ");
   Put(Deluppgift_1(R), 0);
   New_Line(2);
   
   -- Deluppgift_2 --
   
   Put("Mata in ett flyttal: ");
   Get(F);
   Put("Mata in ett tecken: ");
   Get(C);
   
   Put("Den beräknade kvoten mellan ");
   Put(F, 0, 1, 0);
   Put(" och ");
   Put(C & " blir ");
   Put((F / C), 0);
   New_Line(2);
   
   -- Deluppgift_3 --
   
   Deluppgift_3(S, F, Product);
   
   Put("Du matade in strängen: " & S);
   Put(" och flyttalet: ");
   Put(F, 0, 1, 0);
   Put(" och produkten blev ");
   Put(Product);
      
end Test2;
