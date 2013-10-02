<?php

class User
{
	private $name;
	private $meetings;
	private $failFlag = -9999;

	// pass in the string from the users.txt file
	public function __construct($a, $n) {
		$this->name = $a[0];

		// fill $meetings with the meetings which our
		// user has, or 0 if no meeting at that spot
		for ($i = 0; $i < $n; $i++) {
			$this->meetings[$i] = $this->failFlag;
		}

		for ($i = 0; $i < $n; $i++) {
			if (isset($a[1][$i])) {
				$this->meetings[intval($a[1][$i])] = 1;
			}
		}
	}

	// just an accessor
	public function getName() {
		return $this->name;
	}

	// return whether or not this user has a meeting at time $a
	public function hasMeeting($a) {
		return ($this->meetings[$a] != $this->failFlag);
	}

	// print out the row of the table
	// right now goes unused
	public function __toString() {
		return $this->name;
	}
}

?>
