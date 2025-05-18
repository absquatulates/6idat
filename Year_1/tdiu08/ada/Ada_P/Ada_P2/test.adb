-- Ada_P2 --

with Ada.Text_IO;                         use Ada.Text_IO;
with Ada.Integer_Text_IO;                 use Ada.Integer_Text_IO; 
with Ada.Float_Text_IO;                   use Ada.Float_Text_IO;

procedure Test is
   
   -- Deluppgift_1 --
   
   procedure Deluppgift_1 (F: out Float;
			   S: out String;
			   Prod: out Float) is
      
   begin
      
      Put("Mata in ett flyttal: ");
      Get(F);
      Put("Mata in en sträng med exakt 3 tecken: ");
      Get(S);
      
      Prod := F * Float'Value(S);
      
   end Deluppgift_1;
   
   -- Deluppgift_2 --
   
   function Deluppgift_2 (I1, I2, I3: in Integer) return Integer is
      
      Med: Integer;
      
   begin
      
      Med := Integer(Float'Rounding(Float(I1+I2+I3)/Float(3)));
      return Med;
      
   end Deluppgift_2;
   
   -- Deluppgift_3 --
   
   function "-" (Right: in Integer;
		 Left: in Float) return Float is
      
      Diff: Float;
      
   begin
      
      Diff := Float'Rounding(Float(Right) - Left);    
      return Diff;
      
   end "-";
   
   -- Huvudprogram --
   
   I1, I2, I3: Integer;
   F, Prod: Float;
   S: String(1..3);
   
begin
   
   -- Deluppgift_1 --
   Deluppgift_1(F, S, Prod);
   Put("Du matade in flyttalet: ");
   Put(F, 0, 1, 0);
   Put(" och strängen: " & S & " och produkten blev ");
   Put(Prod);
   New_Line(2);
   
   -- Deluppgift_2 --
   Put("Mata in tre heltal: ");
   Get(I1);
   Get(I2);
   Get(I3);
   
   Put("Medelvärdet av dessa är: ");
   Put(Deluppgift_2(I1, I2, I3), 0);
   New_Line(2);
   
   -- Deluppgift_3 --
   Put("Mata in ett heltal: ");
   Get(I1);
   Put("Mata in ett flyttal: ");
   Get(F);
   
   Put("Den beräknade differensen mellan ");
   Put(I1, 0);
   Put(" och ");
   Put(F, 0, 1, 0);
   Put(" blir ");
   Put(I1-F, 0, 1, 0);
    
end Test;
