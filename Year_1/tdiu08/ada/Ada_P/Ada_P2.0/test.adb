-- Ada_P2.0 --

with Ada.Text_IO;                         use Ada.Text_IO;
with Ada.Integer_Text_IO;                 use Ada.Integer_Text_IO; 
with Ada.Float_Text_IO;                   use Ada.Float_Text_IO; 


procedure Test is
   
   -- Deluppgift_1 --
   
   procedure Deluppgift_1 (I: out Integer;
			   S: out String;
			   Sum: out Integer) is
      
      
   begin
      
      Put("Mata in ett heltal: ");
      Get(I);
      
      Put("Mata in en sträng med exakt 3 tecken: ");
      Get(S);
      
      Sum := Integer(Float'Rounding(Float(I) + Float'Value(S)));
            
   end Deluppgift_1;
   
   -- Deluppgift_2;
   
   function "-" (Left: in Float;
		 Right: in Integer) return Float is
      
      Diff: Float;
      
   begin
      
      Diff := Left - Float(Right);
      Diff := Float'Floor(Diff);
      
      return Diff;
      
   end "-";
   
   -- Deluppgift_3 --
   
   function Deluppgift_3 (Radius: in Integer) return Integer is
      
      Area: Integer;
      
   begin
      
      Area := Integer(Float(Radius) * Float(Radius) * 3.14);

      
      return Area;
      
   end Deluppgift_3;
   
   -- HUVUDPROGRAM --
   
   -- Huvudprogrammets deklarationer --
   
   I, Radius: Integer;
   F: Float;
   S: String(1..3);
   Sum: Integer;
   
begin
   
   -- Deluppgift_1 --
   
   Deluppgift_1(I, S, Sum);
   
   Put("Du matade in heltalet: ");
   Put(I, 0);
   Put(" och strängen: " & S);
   Put(" och summan blev ");
   Put(Sum);
   New_Line(2);
   
   -- Deluppgift_2 --
   
   Put("Mata in ett flyttal: ");
   Get(F);
   Put("Mata in ett heltal: ");
   Get(I);
   
   Put("Den beräknade differensen mellan ");
   Put(F, 0, 1, 0);
   Put(" och ");
   Put(I, 0);
   Put(" blir ");
   Put(F - I, 0, 1, 0);
   New_Line(2);
   
   -- Deluppgift_3 --
   
   Put("Mata in längden: ");
   Get(Radius);
   
   Put("Den beräknade arean blev: ");
   Put(Deluppgift_3(Radius), 0);
     
end Test;
