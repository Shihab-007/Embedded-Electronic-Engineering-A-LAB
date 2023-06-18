library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Traffic_TB is
end Traffic_TB;

architecture TB_arch of Traffic_TB is
    -- Component declaration
    component Traffic
        Port (
            Direction: in std_logic_vector (3 downto 0);
            slot: in std_logic
        );
    end component;

    -- Signal declarations
    signal Direction_tb: std_logic_vector (3 downto 0);
    signal slot_tb: std_logic;
    
begin
    -- Instantiate the Traffic module
    UUT: Traffic
        port map (
            Direction => Direction_tb,
            slot => slot_tb
        );

    -- Stimulus process
    Stimulus: process
    begin
        -- Stimulus values for Direction and slot
        Direction_tb <= "0000";
        wait for 20 ns;

        Direction_tb <= "0101";  -- Example direction: West-South
        wait for 20 ns;

        Direction_tb <= "1111";  -- Example direction: East-East
        wait for 20 ns;

        -- Add more test cases as needed

        wait;
    end process Stimulus;

end TB_arch;

