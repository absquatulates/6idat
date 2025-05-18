with Ada.Text_IO;          use Ada.Text_IO;
with Ada.Integer_Text_IO;  use Ada.Integer_Text_IO;

procedure Lektion_1 is
   
   A, I, Summa : Integer;
   
begin
   
   Summa := 0;
   I := 0;
   
   Put("Skriv fem heltal: ");
   
   while I<5 loop
      
      Get(A);
      Summa := Summa + A;
      
      I := I+1;
      
   end loop;
   
   Put("Summan: ");
   Put(Summa, 1);
   
   
end Lektion_1;
