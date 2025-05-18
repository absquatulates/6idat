-- Föreläsning 6 --
-- Rekursion --

with Ada.Text_IO;                         use Ada.Text_IO;
with Ada.Integer_Text_IO;                 use Ada.Integer_Text_IO; 
with Ada.Float_Text_IO;                   use Ada.Float_Text_IO;

--with Ada.Unchecked_Deallocation;          use Ada.Unchecked_Deallocation;


---------------
-- Rekursion --
---------------

procedure Fo6 is
   
   function Factorial (N: in Natural)
		      return Positive is
      
   begin
      
      if N = 0 then
	 return 1;
      else
	 return N * Factorial(N-1);
      end if;
      
   end Factorial;
   
   
   N: Natural;
   
begin
   loop
      begin
	 Put("Mata in ett naturligt tal: ");
	 Get(N);
	 if N > 12 or N < 0 then
	    raise Constraint_Error;
	 end if;
	 Put(N, 0);
	 Put("-fakultet = ");
	 Put(Factorial(N), 0);
	 exit;
	 
	 
      exception
	 when Constraint_Error =>
	    Put_Line("SÄMST");
	    
	    
      end;   
   end loop;
   
end Fo6;


----------------
---- Pekare ----
----------------

--  procedure Fo6 is
   
--     type Integer_Pointer is
--       access Integer;  
   
--     I1, I2: Integer;
--     P1, P2: Integer_Pointer;
   
--  begin
   
--     P1 := new Integer;
--     P1.all := 7;
   
--     P2 := new Integer;
--     P2.all := I2;
   
--     Put(P1.all, 0);
--     New_Line;
--     Put(I2, 0);
   
   
--  end Fo6;

