-- TDIU08 Föreläsning 4 --
-- Kasta undantag, Paket --

with Ada.Text_IO;              use Ada.Text_IO;
with Ada.Integer_Text_IO;      use Ada.Text_Integer_IO;



-- Kasta/Resa Undantag


procedure Fö4 is
   
   
   procedure Get is
      
      Data_Error: exception;
      
   begin
      
      if (FEL!) then
	 Raise Data_Error;
      
   end Get;
   
   procedure Get_Safe is
      
   begin
      
      Get(I);
      
   exception
      when Data_Error =>
	 .
	 .
	 .  
      
   end Get_Safe;
   
   
begin
   
   Get_Safe();
   
   
   
   
   
   
   
   
end Fö4;   


procedure HP is

   Data_Error: exception;
   
   procedure X is
      
   begin
      
      raise Data_Error;
      
   end X;
      
begin
   
   
end HP;



-- Paket

with Time_Handling;      use Time_Handling;

procedure L_T is
   
   T1, T2: Time_Type
     
begin
     
     Get(T1);
     
     if T1 < T2 then
	Blala;
     end if;
     
end L_T;
   
   
   

-- time_handling.ads --

package Time_Handling is
   
-- Publik Del --
-----------------------------------------------------------
   type Time_Type is private;
   
   procedure Get(Item: out Time_Type);
   function "<" (Left, Right: in Time_Type) return Boolean;
   
   Hour_Error: exception;
------------------------------------------------------------
   
private
   type Time_Type is
      record
	 H, M, S: Integer;
      end record;
   
end Time_Handling;



-- time_handling.adb
with Ada.Integer_Text_IO;         use Ada.Integer_Text_IO;

package body Time_Handling is
   
   procedure Get(Item: out Time_Type) is
      
   begin
      
      Get(Item.H);
      Get(
      
      
   end Get;
   
   
end Time_Handling;
