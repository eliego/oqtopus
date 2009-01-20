<?php
	/* Qcodo Development Framework for PHP
	 * http://www.qcodo.com/
	 * 
	 * The Qcodo Development Framework is distributed by QuasIdea Development, LLC
	 * under the terms of The MIT License.  More information can be found at
	 * http://www.opensource.org/licenses/mit-license.php
	 * 
	 * Copyright (c) 2001 - 2006, QuasIdea Development, LLC
	 * 
	 * Permission is hereby granted, free of charge, to any person obtaining a copy of
	 * this software and associated documentation files (the "Software"), to deal in
	 * the Software without restriction, including without limitation the rights to
	 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
	 * of the Software, and to permit persons to whom the Software is furnished to do
	 * so, subject to the following conditions:
	 * 
	 * The above copyright notice and this permission notice shall be included in all
	 * copies or substantial portions of the Software.
	 * 
	 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	 * SOFTWARE.
	 */

	// This file describes the various enumeration classes that are used throughout the Qforms layer

	abstract class QBorderStyle {
		const NotSet = 'NotSet';
		const None = 'none';
		const Dotted = 'dotted';
		const Dashed = 'dashed';
		const Solid = 'solid';
		const Double = 'double';
		const Groove = 'groove';
		const Ridge = 'ridge';
		const Inset = 'inset';
		const Outset = 'outset';
	}

	abstract class QDisplayStyle {
		const None = 'none';
		const Block = 'block';
		const Inline = 'inline';
		const NotSet = 'NotSet';
	}

	abstract class QTextAlign {
		const Left = 'left';
		const Right = 'right';
	}

	abstract class QRepeatDirection {
		const Horizontal = 'Horizontal';
		const Vertical = 'Vertical';
	}

	abstract class QGridLines {
		const None = 'none';
		const Horizontal = 'horizontal';
		const Vertical = 'vertical';
		const Both = 'both';
	}

	abstract class QSelectionMode {
		const Single = 'Single';
		const Multiple = 'Multiple';
		const None = 'None';
	}

	abstract class QTextMode {
		const SingleLine = 'SingleLine';
		const MultiLine = 'MultiLine';
		const Password = 'Password';
	}
	
	abstract class QHorizontalAlign {
		const NotSet = 'NotSet';
		const Left = 'left';
		const Center = 'center';
		const Right = 'right';
		const Justify = 'justify';
	}

	abstract class QVerticalAlign {
		const NotSet = 'NotSet';
		const Top = 'top';
		const Middle = 'middle';
		const Bottom = 'bottom';
	}

	abstract class QBorderCollapse {
		const NotSet = 'NotSet';
		const Separate = 'Separate';
		const Collapse = 'Collapse';
	}
	
	abstract class QDateTimePickerType {
		const Date = 'Date';
		const DateTime = 'DateTime';
		const DateTimeSeconds = 'DateTimeSeconds';
		const Time = 'Time';
		const TimeSeconds = 'TimeSeconds';
	}

	abstract class QCalendarType {
		const DateOnly = 'DateOnly';
		const DateTime = 'DateTime';
		const DateTimeSeconds = 'DateTimeSeconds';
		const TimeOnly = 'TimeOnly';
		const TimeSecondsOnly = 'TimeSecondsOnly';
	}

	abstract class QDateTimePickerFormat {
		const MonthDayYear = 'MonthDayYear';
		const DayMonthYear = 'DayMonthYear';
		const YearMonthDay = 'YearMonthDay';
	}

	abstract class QCrossScripting {
		const Allow = 'Allow';
		const HtmlEntities = 'HtmlEntities';
		const Deny = 'Deny';
	}
	
	abstract class QCallType {
		const Server = 'Server';
		const Ajax = 'Ajax';
		const None = 'None';
	}
	
	abstract class QPosition {
		const Relative = 'relative';
		const Absolute = 'absolute';
		const Fixed = 'fixed';
		const NotSet = 'NotSet';
	}
?>