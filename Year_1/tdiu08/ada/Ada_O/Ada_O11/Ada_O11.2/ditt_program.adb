-- Ada_O11.2 --
-- hugho678: Samarbetat med carbj841, Carl Björlin, samma program

with Ada.Command_Line;      use Ada.Command_Line; 
with Ada.Text_IO;           use Ada.Text_IO; 


procedure Ditt_Program is
   
begin
   
   if Argument_Count = 0 then
      Put("Inga argument angivna.");
   elsif Argument_Count /=3 then
      Put("Fel antal argument angivna.");
   elsif Argument(1) = Command_Name or Command_Name(3..Command_Name'Last) = Argument(1) then       
      Put("Error! Input file """ & Argument(1) & """ cannot be same as the program itself!");
   elsif Argument(1) = Argument(2) or (Argument(1)(3..Argument(1)'Last) = Argument(2) and Argument(1)(1..1) = ".") 
     or (Argument(2)(3..Argument(2)'Last) = Argument(1) and Argument(2)(1..1) = ".") then   
      Put("Error! Output file """ & Argument(2) & """ cannot be same as input file!");
   elsif Argument(2) = Command_Name or Argument(2) = Command_Name(3..Command_Name'Last) then
      Put("Error! Output file """ & Argument(2) & """ cannot be same as the program itself!");
   else
      Put("Meddelande: ");         
      For I in 1..Integer'Value(Argument(3)) loop
	 Put(Argument(1)); 
      end loop;
      Put(Argument(2));
      New_Line;
      Put("Programmet """ & Command_Name & """ avslutas.");
   end if;
   
end Ditt_Program; 
