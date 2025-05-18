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
