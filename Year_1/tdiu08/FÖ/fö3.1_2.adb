-- TDIU08 Föreläsning 3.1_2
-- UNDANTAG --

with Ada.Text_IO;            use Ada.Text_IO;
with Ada.Integer_Text_IO;    use Ada.Integer_Text_IO;


procedure Skit2 is
   
   I: Integer;
   
begin 
   
   loop
      begin
	 Get(I);
	 exit;
   
      exception
   
	 when Data_Error =>
	    Put("Fel datatyp!");
	    Skip_Line;
      end;
    end loop;  
      
end Skit2;   
