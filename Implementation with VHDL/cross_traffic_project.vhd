library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Traffic is
	Port ( 
		Direction: in std_logic_vector (3 downto 0);
		slot: in std_logic
	);
end Traffic;
    -- North is "00"
   -- West is "01" 
   -- South is "10"
   -- East is "11"
architecture behavior of Traffic is
	type t_state is (NW, NE, SE, SW);
	signal state: t_state;
	signal FirstBit:  std_logic_vector (1 downto 0);
	signal SecondBit: std_logic_vector (1 downto 0);
begin

	FirstBit <= Direction(3) & Direction(2);
	SecondBit <= Direction(1) & Direction(0);

	Process (Direction) is
	begin

		if (Direction /= "0000" and Direction /= "1111") then  --no action is expected if the directions are either Nort-North or East-East
			case State is
				when NW =>   
					if (SecondBit /= "01" and slot = '1') then -- Check if the second bit of the direction is different from "01" and there is a car waiting
						State <= SW; -- Go to the next state
					else
						State <= NW; -- Otherwise remain to the state
					end if;
					
					if (SecondBit = "01") then --If the second bit of the direction is the same as the second bit of the state.
						report "Exit successful";
					end if;

				when SW =>
					if (SecondBit /= "10" and slot = '1') then -- Check if the second bit of the direction is different from "10" and there is a car waiting
						State <= SE;
					else
						State <= SW;
					end if;
					
					if (SecondBit = "10") then --If the second bit of the direction is the same as the second bit of the state
						report "Exit successful";
					end if;

				when SE =>
					if (SecondBit /= "11" and slot = '1') then -- if there is a car waiting at the the east intersection
						State <= NE;
					else
						State <= SE;
					end if;
					
					if (SecondBit = "11") then -- If the second bit of the direction is the same as the second bit of the state
						report "Exit successful";
					end if;

				when NE =>
					if (SecondBit /= "00" and slot = '1') then  -- if there is a car waiting at the North intersection
						State <= NW;
					else
						State <= NE;
					end if;
					
					if (SecondBit = "00") then -- if there is no car at the north intersection
                                      
						report "Exit successful"; -- Exit the state
					end if;

				when others =>
					report "The state is not present";
			end case;
		end if;
	end process;
end behavior;

