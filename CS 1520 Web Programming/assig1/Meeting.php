<?php

class Meeting
{
	private $day;
	private $time;

	// just set the time
	public function __construct($a, $b) {
		$this->day = $a;
		$this->time = $b;
	}

	public function day() {
		return $this->day;
	}

	public function time() {
		return $this->time;
	}

	// print out the meeting time in a properly formatted way
	public function __toString() {
		$ans;

		$oldTimezone = date_default_timezone_get();
		
		date_default_timezone_set('UTC');

		$ans = date(" l ", strtotime($this->day));
		$ans .= "<br>";
		$ans .= date(" m/d/y ", strtotime($this->day));
		$ans .= "<br>";
		$ans .= date(" g:i a", strtotime($this->time));
		
		date_default_timezone_set((string)$oldTimezone);

		return $ans;
	}
}

?>
