-- Ada_O11.2 --
-- hugho678: Samarbetat med carbj841, Carl Björlin, samma program

with Ada.Text_IO;                     use Ada.Text_IO;
with Ada.Command_Line;                use Ada.Command_Line;
  
procedure Ditt_program is
   
   procedure ERROR is
      
   begin

      if Argument(1) = Command_Name or Argument(1) = Command_Name(3..Command_Name'Last) then
	 Put("Error! Input file " & '"' & Argument(1) & '"' &  " cannot be same as the program itself!");  
	 
      elsif Argument(2) = Command_Name or Argument(2) = Command_Name(3..Command_Name'Last) then
	 Put("Error! Output file " &'"' & Argument(2) & '"' &  " cannot be same as the program itself!"); 

      elsif Argument(1) = Argument(2) or (Argument(1) = Argument(2)(3..Argument(2)'Last) and Argument(2)(1..1) = ".")
	or (Argument(1)(3..Argument(1)'Last) = Argument(2) and Argument(1)(1..1) = ".") then
	 Put("Error! Output file " & '"' & Argument(2) & '"' & " cannot be same as input file!");
	 
      else
	 Put("Meddelande: ");
	 for I in 1..Integer'Value(Argument(3)) loop
	    Put(Argument(1));
	 end loop;
	 Put(Argument(2));
	 New_Line;
	 Put("Programmet " & '"' & Command_Name & '"' &  " avslutas.");
      end if;
      
   end ERROR;
   
   procedure Arg is
      
   begin
      
      if Argument(1) = Command_Name or Argument(2) = Command_Name or Argument(1) = Argument(2) or Argument(1) = Argument(2)(3..Argument(2)'Last)
	or Argument(1)(3..Argument(1)'Last) = Argument(2) or Argument(1) = Command_Name(3..Command_Name'Last) or
	Argument(2) = Command_Name(3..Command_Name'Last) then
	 ERROR;
	 
      else
	 Put("Meddelande: ");
	 for I in 1..Integer'Value(Argument(3)) loop
	    Put(Argument(1));
	 end loop;
	 Put(Argument(2));
	 New_Line;
	 Put("Programmet " & '"' & Command_Name & '"' &  " avslutas.");

      end if;    
      
   end Arg; 
   
   -- Huvudprogram --
   
begin
   
   case Argument_Count is
      when 0            => Put("Inga argument angivna."); 
      when 3            => Arg;      
      when others       => Put("Fel antal argument angivna.");
   end case;    

end Ditt_program;
