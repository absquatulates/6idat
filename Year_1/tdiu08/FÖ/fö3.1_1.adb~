-- TDIU08 Föreläsning 3.1_1
-- POSTER --

with Ada.Text_IO;              use Ada.Text_IO;
with Ada.Integer_Text_IO;      use Ada.Text_Integer_IO;


procedure Skit is
   
   -- Datatyp: Person_Type
   
   type Person_Type is
      record
	 
	 Name: String(1..30);
	 Shoe_Size: Float;
	 Age: Integer;
	 Adress: String(1..50);
	 Gender: Boolean;
	 Happy_Customer: Integer;
	 
      -- Child: Person_Type; --  Fungerar ej, en datatyp kan inte inehålla sig själv!
      end record;
   
   
   -- Datatyp: Parent_Type
   
   type Parent_Type is
      record
	 
	 Name: String(1..30);
	 Shoe_Size: Float;
	 Age: Integer;
	 Adress: String(1..50);
	 Gender: Boolean;
	 Happy_Customer: Integer;
	 
	 Child: Person_Type; -- Fungerar!
	 
      end record; 
   
   
   -- Underprogram HÄR!
   
   
   Parent: Parent_Type;  
   Person, Person_2: Person_Type;
   
begin
   
   Person := Person_2;
   
   Person.Age := 32;
   Put(Person.Age);
   
   if Person = Person_2 then
      
   end if;
      
--if Person > Person_2 then \
--                           }  Funkar ej!
-- end if;                  /  
   
   Parent.Child := Person;
   Parent.Child.Shoe_Size := 41.0;
   
   
end Skit;


  
