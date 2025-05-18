-- Ada.O2 --
-- hugho678: Samarbetat med carbj841, Carl Björlin, samma program

with Ada.Text_IO;                                 use Ada.Text_IO;
with Ada.Integer_Text_IO;                         use Ada.Integer_Text_IO;
with Ada.Float_Text_IO;                           use Ada.Float_Text_IO; 

procedure Test is
   
   --- UNDERPROGRAM ---
   
   -- Deluppgift 1 -- operator
   
   function "-" (Left: in Integer; Right: in Float) return Float is
      
      Diff: Float;
      
   begin
      
      Diff := Float(Left) - Right;
      
      return Diff;
      
   end "-";
   
   -- Deluppgift 2 -- procedure
   
   procedure Deluppgift_2 (S: in out String; B: out Boolean) is    
      
   begin
      
      if S(S'Last) = 'S' or S(S'Last) = 's' then
	 B := True;
      else
	 B := False;
	 S(S'Last) := 's';
      end if; 
      
   end Deluppgift_2; 
   
   -- Deluppgift 3 -- function
   
   function Deluppgift_3 (C: in  Character) return Boolean is
      
      B: Boolean;
      
   begin
      
      if C = 'S' or C = 's' then
	 B := True;
      else
	 B := False;
      end if;
      
      return B;	   
      
   end Deluppgift_3;
   
   -- Huvudprogrammets deklareringar

   I: Integer;
   F: Float;
   C: Character;
   S: String(1..5);
   B: Boolean;
   
   -- HUVUDPROGRAM --
   
begin
   
   -- Deluppgift 1
   
   Put("Mata in ett heltal och ett flyttal: ");
   Get(I);
   Get(F);
   
   Put("Differensen mellan dem är ");
   Put(I - F, 0, 2, 0);
   New_Line(2); 
   
   -- Deluppgift_2
   
   Put("Skriv in ett 5 tecken långt engelskt substantiv: ");
   Get(S);
   
   Deluppgift_2(S, B);
   Put("Ordet " & S & " var troligtvis");
   
   if B = False then
      Put(" inte");
   end if;
   Put(" i plural från början");
   
   New_Line(2);
   
   -- Deluppgift_3
   
   Put("Mata in ett tecken: ");
   Get(C);
   
   Put("Tecknet var ");
   
   if Deluppgift_3(C) = False then
      Put("inte ");
   end if;
   
   Put("sant");     
   
end Test;   
