-- TDIU08 Föreläsning 3.2 --

--  procedure Skit3 is -- procedure Golf is
   
--     type Golf_Type is
--       array (1..18) of Integer;
     
--       Result, Result_2: Golf_Type;
     
   
--    --  A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18: Integer; -- behövs inte då --
   
--  begin
   
--       for I in 1..18 loop
--  	Result(I) := 0;
--       end loop;
     
--       Put(Result(3));
     
--       if Result = Result_2 then
--       end if;  
   
   
--end Skit3; -- end Golf; 

------------------------------------------------------------------------------
------------------------------------------------------------------------------

--  with Ada.Text_IO;              use Ada.Text_IO;
--  with Ada.Integer_Text_IO;      use Ada.Integer_Text_IO;

--  procedure Skit3 is
   
--     type Ttt_Type is
--       array (1..3, 1..3) of Character;
     
--     Board: Ttt_Type;
     
--  begin
   
--     Board(1,1) := 'X';
--     Put(Board(1,3));
   
--  end Skit3;

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

with Ada.Text_IO;              use Ada.Text_IO;
with Ada.Integer_Text_IO;      use Ada.Integer_Text_IO;

procedure Skit3 is
   
   type Row_Type is
     array (1..3) of Character;
   
   type Ttt2_Type is
     array (1..3) of Row_Type;
     
   Board2: Ttt2_Type;
     
begin
   
   Board2(1)(1) := 'X';
  -- Put(Board2(1));
  --  New_Line;
   Put(Board2(1)(1));
   
end Skit3;
