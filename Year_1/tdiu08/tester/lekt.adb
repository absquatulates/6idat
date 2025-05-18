-- LEKTION 3 --

with Ada.Text_IO;              use Ada.Text_IO;
with Ada.Integer_Text_IO;      use Ada.Integer_Text_IO;

procedure Lekt is
   
   procedure Get(X: out Complex_Type) is
      
      CH: Character;
      
   begin
      
      Get(X.Re);
      Get(CH);
      Get(X.Im);
      Get(CH);
      
   end Get;   
   
   
   function "+" (Left, Right: Complex_Type) return Complex_Type is
      
      Sum: Complex_Type;
      
   begin
      
      Sum.Re := Left.Re + Right.Re;
      Sum.Im := Left.Im + Right.Im;
      
      
      return Sum;
      
   end "+";
   
   
   procedure Put (X: in Complex_Type) is
      
   begin
      
      Put(X.Re);
      
      if (X.Im < 0) then
	 Put(X.Im);
      else
	 Put("+");
	 Put(X.Im);
      end if;
      
   end Put;   
   
   
   type Complex_Type is
      record
	 Re: Integer;
	 Im: Integer;
	 
      end record;	 
   
   A, B, Sum: Complex_Type;
   
begin
   
   Put("Skriv in z komplext tal: ");
   Get(A);
   Get(B);
   
   Put("Summa: ");
   Put(A+B);
   
   
   
   
end Lekt;   








--  procedure Lekt is
   
   
--     procedure Las_In (A: out Falt) is
      
      
--     begin
--        Put("Skriv 5 heltal: ");
      
--        for I in A'Range loop
--  	 Get(A(I));
--        end loop; 
      
--        Put(A);
      
--     end Las_In;  
   
--     procedure Skriv_Ut (A: in Falt) is
      
--        Summa: Integer;
      
--     begin
      
--        for I in A'Range loop
	 
--  	 Summa:= A(I) + Summa;
	 
--        end loop;
      
--        New_Line;
--        Put("Summa: ");
--        Put(Summa, 1);
      
--     end Skriv_Ut;   
   
   
--     type Falt is
--       array (1..5) of Integer;
   
--     A: Falt;
   
 
   
--  begin
   
--     Las_In(A);
--     --  Summera();
--     Skriv_Ut(A);
       
   
--  end Lekt;
   
