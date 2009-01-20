/**
 * The Qcodo Object is used for everything in Qcodo
 */
var qcodo = {
	initialize: function() {

		////////////////////////////////////////////
		// Initialize: Browser-related functionality
		////////////////////////////////////////////

		this.isBrowser = function(intBrowserType) {
			return (intBrowserType & qcodo._intBrowserType);
		}
		this.IE = 1;
		this.FIREFOX = 2;
		this.SAFARI = 4;
		this.OTHER = 8;
		this._intBrowserType = this.OTHER;

		if (navigator.userAgent.toLowerCase().indexOf("msie") >= 0) {
			this._intBrowserType = this.IE;
		} else if (navigator.userAgent.toLowerCase().indexOf("firefox") >= 0) {
			this._intBrowserType = this.FIREFOX;
		} else if (navigator.userAgent.toLowerCase().indexOf("safari") >= 0) {
			this._intBrowserType = this.SAFARI;
		} else {
			this._intBrowserType = this.OTHER;
		}


		////////////////////////////////////////////
		// Initialize: Form-related functionality
		////////////////////////////////////////////

		this.registerForm = function() {
			// "Lookup" the QForm's FormId
			var strFormId = document.getElementById("Qform__FormId").value;

			// Register the Various Hidden Form Elements needed for QForms
			this.registerFormHiddenElement("Qform__FormControl", strFormId);
			this.registerFormHiddenElement("Qform__FormEvent", strFormId);
			this.registerFormHiddenElement("Qform__FormParameter", strFormId);
			this.registerFormHiddenElement("Qform__FormCallType", strFormId);
			this.registerFormHiddenElement("Qform__FormUpdates", strFormId);
			this.registerFormHiddenElement("Qform__FormCheckableControls", strFormId);
		}

		this.registerFormHiddenElement = function(strId, strFormId) {
			var objHiddenElement = document.createElement("input");
			objHiddenElement.type = "hidden";
			objHiddenElement.id = strId;
			objHiddenElement.name = strId;
			document.getElementById(strFormId).appendChild(objHiddenElement);
		}

		////////////////////////////////////////////
		// PostBack and AjaxPostBack
		////////////////////////////////////////////

		this.postBack = function(strForm, strControl, strEvent, strParameter) {
			var objForm = document.getElementById(strForm);
			objForm.Qform__FormControl.value = strControl;
			objForm.Qform__FormEvent.value = strEvent;
			objForm.Qform__FormParameter.value = strParameter;
			objForm.Qform__FormCallType.value = "Server";
			objForm.Qform__FormUpdates.value = this.formUpdates();
			objForm.Qform__FormCheckableControls.value = this.formCheckableControls(strForm, "Server");
			objForm.submit();
		}

		this.formUpdates = function() {
			var strToReturn = "";
			for (var intIndex = 0; intIndex < qcodo.controlModifications.length; intIndex++) {
				strToReturn += qcodo.controlModifications[intIndex] + "\n";
			}

			qcodo.controlModifications = new Array();
			return strToReturn;
		}
		
		this.formCheckableControls = function(strForm, strCallType) {
			var objForm = document.getElementById(strForm);
			var strToReturn = "";

			for (var intIndex = 0; intIndex < objForm.elements.length; intIndex++) {
				if (((objForm.elements[intIndex].type == "checkbox") ||
					 (objForm.elements[intIndex].type == "radio")) &&
					((strCallType == "Ajax") ||
					(!objForm.elements[intIndex].disabled)))
					strToReturn += " " + objForm.elements[intIndex].id;
			}

			if (strToReturn.length > 0)
				return strToReturn.substring(1);
			else
				return "";
		}

		this.ajaxQueue = new Array();

		this.postAjax = function(strForm, strControl, strEvent, strParameter, strWaitIconControlId) {
//			alert(strForm + " " + strControl + " " + strEvent + " " + strParameter);
			// Figure out if Queue is Empty
			var blnQueueEmpty = false;
			if (qcodo.ajaxQueue.length == 0)
				blnQueueEmpty = true;

			// Enqueue the AJAX Request
			qcodo.ajaxQueue.push(new Array(strForm, strControl, strEvent, strParameter, strWaitIconControlId));

			// If the Queue was originally empty, call the Dequeue
			if (blnQueueEmpty)
				qcodo.dequeueAjaxQueue();
		}
		
		this.clearAjaxQueue = function() {
			qcodo.ajaxQueue = new Array();
		}

		this.objAjaxWaitIcon = null;

		this.dequeueAjaxQueue = function() {
			if (qcodo.ajaxQueue.length > 0) {
				strForm = this.ajaxQueue[0][0];
				strControl = this.ajaxQueue[0][1];
				strEvent = this.ajaxQueue[0][2];
				strParameter = this.ajaxQueue[0][3];
				strWaitIconControlId = this.ajaxQueue[0][4];

				// Display WaitIcon (if applicable)
				if (strWaitIconControlId) {
					this.objAjaxWaitIcon = this.getWrapper(strWaitIconControlId);
					if (this.objAjaxWaitIcon)
						this.objAjaxWaitIcon.style.display = 'inline';
				}

				var objForm = document.getElementById(strForm);
				objForm.Qform__FormControl.value = strControl;
				objForm.Qform__FormEvent.value = strEvent;
				objForm.Qform__FormParameter.value = strParameter;
				objForm.Qform__FormCallType.value = "Ajax";
				objForm.Qform__FormUpdates.value = qcodo.formUpdates();
				objForm.Qform__FormCheckableControls.value = this.formCheckableControls(strForm, "Ajax");

				var strPostData = "";
				for (var i = 0; i < objForm.elements.length; i++) {
					switch (objForm.elements[i].type) {
						case "checkbox":
						case "radio":
							if (objForm.elements[i].checked) {
								var strTestName = objForm.elements[i].name + "_";
								if (objForm.elements[i].id.substring(0, strTestName.length) == strTestName)
									strPostData += "&" + objForm.elements[i].name + "=" + objForm.elements[i].id.substring(strTestName.length);
								else
									strPostData += "&" + objForm.elements[i].id + "=" + "1";
							}
							break;

						case "select-multiple":
							var blnOneSelected = false;
							for (var intIndex = 0; intIndex < objForm.elements[i].options.length; intIndex++)
								if (objForm.elements[i].options[intIndex].selected) {
									strPostData += "&" + objForm.elements[i].name + "=";
									strPostData += objForm.elements[i].options[intIndex].value;
								}
							break;

						default:
							strPostData += "&" + objForm.elements[i].id + "=";

							// For Internationalization -- we must escape the element's value properly
							var strPostValue = objForm.elements[i].value;
							strPostValue = strPostValue.replace(/&/g, escape('&'));
							strPostValue = strPostValue.replace(/\+/g, "%2B");
							strPostData += strPostValue;
							break;
					}
				}

				var strUri = objForm.action;

				var objRequest;
				if (window.XMLHttpRequest) {
					objRequest = new XMLHttpRequest();
				} else if (typeof ActiveXObject != "undefined") {
					objRequest = new ActiveXObject("Microsoft.XMLHTTP");
				}

				if (objRequest) {
					objRequest.open("POST", strUri, true);
					objRequest.setRequestHeader("Method", "POST " + strUri + " HTTP/1.1");
					objRequest.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");

					objRequest.onreadystatechange = function() {
						if (objRequest.readyState == 4) {
							try {
								var objXmlDoc = objRequest.responseXML;
//								qcodo.logMessage(objRequest.responseText, true);
//								alert('AJAX Response Received');

								if ((!objXmlDoc) || (!objXmlDoc.documentElement)) {
									alert("An error occurred during AJAX Response parsing.\r\n\r\nThe error response will appear in a new popup.");
									var objErrorWindow = window.open('about:blank', 'qcodo_error','menubar=no,toolbar=no,location=no,status=no,scrollbars=yes,resizable=yes,width=1000,height=700,left=50,top=50');
									objErrorWindow.focus();
									objErrorWindow.document.write(objRequest.responseText);
									return;
								} else {
									var intLength = 0;
	
									// Go through Controls
									var objXmlControls = objXmlDoc.getElementsByTagName('control');
									intLength = objXmlControls.length;

									for (var intIndex = 0; intIndex < intLength; intIndex++) {
										var strControlId = objXmlControls[intIndex].attributes.getNamedItem('id').nodeValue;

										var strControlHtml = "";
										if (objXmlControls[intIndex].firstChild)
											strControlHtml = objXmlControls[intIndex].firstChild.nodeValue;
										if (qcodo.isBrowser(qcodo.FIREFOX))
											strControlHtml = objXmlControls[intIndex].textContent;

										// Perform Callback Responsibility
										if (strControlId == "Qform__FormState") {
											var objFormState = document.getElementById(strControlId);
											objFormState.value = strControlHtml;							
										} else {
											var objSpan = document.getElementById(strControlId + "_ctl");
											if (objSpan)
												objSpan.innerHTML = strControlHtml;
										}
									}

									// Go through Commands
									var objXmlCommands = objXmlDoc.getElementsByTagName('command');
									intLength = objXmlCommands.length;
	
									for (var intIndex = 0; intIndex < intLength; intIndex++) {
										if (objXmlCommands[intIndex] && objXmlCommands[intIndex].firstChild) {
											var strCommand = objXmlCommands[intIndex].firstChild.nodeValue;
											eval(strCommand);
										}
									}
								}
							} catch (objExc) {
								alert(objExc.message + "\r\non line number " + objExc.lineNumber);
								alert("An error occurred during AJAX Response handling.\r\n\r\nThe error response will appear in a new popup.");
								var objErrorWindow = window.open('about:blank', 'qcodo_error','menubar=no,toolbar=no,location=no,status=no,scrollbars=yes,resizable=yes,width=1000,height=700,left=50,top=50');
								objErrorWindow.focus();
								objErrorWindow.document.write(objRequest.responseText);
								return;
							}

							// Perform the Dequeue
							qcodo.ajaxQueue.reverse();
							qcodo.ajaxQueue.pop();
							qcodo.ajaxQueue.reverse();
							
							// Hid the WaitIcon (if applicable)
							if (qcodo.objAjaxWaitIcon)
								qcodo.objAjaxWaitIcon.style.display = 'none';

							// If there are still AjaxEvents in the queue, go ahead and process/dequeue them
							if (qcodo.ajaxQueue.length > 0)
								qcodo.dequeueAjaxQueue();
						}
					}

					objRequest.send(strPostData);
				}
			}
		}


		////////////////////////////////////////////
		// Initialize: Controls-related functionality
		////////////////////////////////////////////

		this.getControl = function(mixControl) {
			if (typeof(mixControl) == 'string')
				return document.getElementById(mixControl);
			else
				return mixControl;
		}

		this.getWrapper = function(mixControl) {
			var objControl; if (!(objControl = qcodo.getControl(mixControl))) return;

			if (objControl)
				return this.getControl(objControl.id + "_ctl");
			else
				return null;
		}



		/////////////////////////////
		// Register Control - General
		/////////////////////////////
		
		this.controlModifications = new Array();
		this.javascriptStyleToQcodo = new Array();
		this.javascriptStyleToQcodo["backgroundColor"] = "BackColor";
		this.javascriptStyleToQcodo["borderColor"] = "BorderColor";
		this.javascriptStyleToQcodo["borderStyle"] = "BorderStyle";
		this.javascriptStyleToQcodo["border"] = "BorderWidth";
		this.javascriptStyleToQcodo["height"] = "Height";
		this.javascriptStyleToQcodo["width"] = "Width";

		this.javascriptWrapperStyleToQcodo = new Array();
		this.javascriptWrapperStyleToQcodo["position"] = "Position";
		this.javascriptWrapperStyleToQcodo["top"] = "Top";
		this.javascriptWrapperStyleToQcodo["left"] = "Left";

		this.recordControlModification = function(strControlId, strProperty, strNewValue) {
			qcodo.controlModifications[qcodo.controlModifications.length] = strControlId + " " + strProperty + " " + strNewValue;
		}

		this.registerControl = function(mixControl) {
			var objControl; if (!(objControl = qcodo.getControl(mixControl))) return;

			// Link the Wrapper and the Control together
			var objWrapper = this.getWrapper(objControl);
			objControl.wrapper = objWrapper;
			objWrapper.control = objControl;

			// Create New Methods, etc.
			// Like: objWrapper.something = xyz;

			
			// Updating Style-related Things
			objWrapper.updateStyle = function(strStyleName, strNewValue) {
				var objControl = this.control;
				
				switch (strStyleName) {
					case "className":
						objControl.className = strNewValue;
						qcodo.recordControlModification(objControl.id, "CssClass", strNewValue);
						break;
						
					case "parent":
						if (strNewValue) {
							var objNewParentControl = qcodo.getControl(strNewValue);
							objNewParentControl.appendChild(this);
							qcodo.recordControlModification(objControl.id, "Parent", strNewValue);
						} else {
							var objParentControl = this.parentNode;
							objParentControl.removeChild(this);
							qcodo.recordControlModification(objControl.id, "Parent", "");
						}
						break;
					
					case "displayStyle":
						objControl.style.display = strNewValue;
						qcodo.recordControlModification(objControl.id, "DisplayStyle", strNewValue);
						break;

					case "display":
						if (strNewValue) {
							objWrapper.style.display = "inline";
							qcodo.recordControlModification(objControl.id, "Display", "1");
						} else {
							objWrapper.style.display = "none";
							qcodo.recordControlModification(objControl.id, "Display", "0");
						}
						break;

					case "enabled":
						if (strNewValue) {
							objWrapper.control.disabled = false;
							qcodo.recordControlModification(objControl.id, "Enabled", "1");
						} else {
							objWrapper.control.disabled = true;
							qcodo.recordControlModification(objControl.id, "Enabled", "0");
						}
						break;

					default:
						if (qcodo.javascriptWrapperStyleToQcodo[strStyleName]) {
							this.style[strStyleName] = strNewValue;
							qcodo.recordControlModification(objControl.id, qcodo.javascriptWrapperStyleToQcodo[strStyleName], strNewValue);
						} else {
							objControl.style[strStyleName] = strNewValue;
							if (qcodo.javascriptStyleToQcodo[strStyleName])
								qcodo.recordControlModification(objControl.id, qcodo.javascriptStyleToQcodo[strStyleName], strNewValue);
						}
						break;
				}
			}

			// Positioning-related functions

			objWrapper.getAbsolutePosition = function() {
				var intOffsetLeft = 0;
				var intOffsetTop = 0;

				var objControl = this.control;

				while (objControl) {
					// If we are IE, we don't want to include calculating
					// controls who's wrappers are position:relative
					if ((objControl.wrapper) && (objControl.wrapper.style.position == "relative")) {
						
					} else {
						intOffsetLeft += objControl.offsetLeft;
						intOffsetTop += objControl.offsetTop;
					}
					objControl = objControl.offsetParent;
				}

				return {x:intOffsetLeft, y:intOffsetTop};
			}

			objWrapper.setAbsolutePosition = function(intNewX, intNewY, blnBindToParent) {
				var objControl = this.offsetParent;

				while (objControl) {
					intNewX -= objControl.offsetLeft;
					intNewY -= objControl.offsetTop;
					objControl = objControl.offsetParent;
				}

				if (blnBindToParent) {
					if (this.parentNode.nodeName.toLowerCase() != 'form') {
						// intNewX and intNewY must be within the parent's control
						intNewX = Math.max(intNewX, 0);
						intNewY = Math.max(intNewY, 0);

						intNewX = Math.min(intNewX, this.offsetParent.offsetWidth - this.offsetWidth);
						intNewY = Math.min(intNewY, this.offsetParent.offsetHeight - this.offsetHeight);
					}
				}

				this.updateStyle("left", intNewX + "px");
				this.updateStyle("top", intNewY + "px");
			}

			objWrapper.setDropZoneMaskAbsolutePosition = function(intNewX, intNewY, blnBindToParent) {
				var objControl = this.offsetParent;

				while (objControl) {
					intNewX -= objControl.offsetLeft;
					intNewY -= objControl.offsetTop;
					objControl = objControl.offsetParent;
				}

				if (blnBindToParent) {
					if (this.parentNode.nodeName.toLowerCase() != 'form') {
						// intNewX and intNewY must be within the parent's control
						intNewX = Math.max(intNewX, 0);
						intNewY = Math.max(intNewY, 0);

						intNewX = Math.min(intNewX, this.offsetParent.offsetWidth - this.offsetWidth);
						intNewY = Math.min(intNewY, this.offsetParent.offsetHeight - this.offsetHeight);
					}
				}

				this.dropZoneMask.style.left = intNewX + "px";
				this.dropZoneMask.style.top = intNewY + "px";
			}

			objWrapper.setMaskOffset = function(intDeltaX, intDeltaY) {
				var objAbsolutePosition = this.getAbsolutePosition();
				this.mask.style.left = (objAbsolutePosition.x + intDeltaX) + "px";
				this.mask.style.top = (objAbsolutePosition.y + intDeltaY) + "px";
			}

			objWrapper.containsPoint = function(intX, intY) {
				var objAbsolutePosition = this.getAbsolutePosition();
				if ((intX >= objAbsolutePosition.x) && (intX <= objAbsolutePosition.x + this.control.offsetWidth) &&
					(intY >= objAbsolutePosition.y) && (intY <= objAbsolutePosition.y + this.control.offsetHeight))
					return true;
				else
					return false;
			}

			// Toggle Display / Enabled
			objWrapper.toggleDisplay = function(strShowOrHide) {
				// Toggles the display/hiding of the entire control (including any design/wrapper HTML)
				// If ShowOrHide is blank, then we toggle
				// Otherwise, we'll execute a "show" or a "hide"
				if (strShowOrHide) {
					if (strShowOrHide == "show")
						this.updateStyle("display", true);
					else
						this.updateStyle("display", false);
				} else
					this.updateStyle("display", (this.style.display == "none") ? true : false);
			}

			objWrapper.toggleEnabled = function(strEnableOrDisable) {
				if (strEnableOrDisable) {
					if (strEnableOrDisable == "enable")
						this.updateStyle("enabled", true);
					else
						this.updateStyle("enabled", false);
				} else
					this.updateStyle("enabled", (this.control.disabled) ? true : false);
			}

			objWrapper.registerClickPosition = function(objEvent) {
				objEvent = (objEvent) ? objEvent : ((typeof(event) == "object") ? event : null);
				qcodo.handleEvent(objEvent);

				var intX = qcodo.mouse.x - this.getAbsolutePosition().x;
				var intY = qcodo.mouse.y - this.getAbsolutePosition().y;

				// Random IE Check
				if (qcodo.isBrowser(qcodo.IE)) {
					intX = intX - 2;
					intY = intY - 2;
				}

				document.getElementById(this.control.id + "_x").value = intX;
				document.getElementById(this.control.id + "_y").value = intY;				
			}

			objWrapper.addToDropZoneGrouping = function(strGroupingId, blnAllowSelf, blnAllowSelfParent) {
				if (!qcodo.dropZoneGrouping[strGroupingId])
					qcodo.dropZoneGrouping[strGroupingId] = new Array();
				qcodo.dropZoneGrouping[strGroupingId][this.control.id] = this;
				qcodo.dropZoneGrouping[strGroupingId]["__allowSelf"] = (blnAllowSelf) ? true : false;
				qcodo.dropZoneGrouping[strGroupingId]["__allowSelfParent"] = (blnAllowSelfParent) ? true : false;

				qcodo.registerControlDropZoneTarget(this.control);
			}

			objWrapper.removeFromDropZoneGrouping = function(strGroupingId) {
				if (!qcodo.dropZoneGrouping[strGroupingId])
					qcodo.dropZoneGrouping[strGroupingId] = new Array();
				else
					qcodo.dropZoneGrouping[strGroupingId][this.control.id] = false;
			}

			objWrapper.a2DZG = objWrapper.addToDropZoneGrouping;
			objWrapper.rfDZG = objWrapper.removeFromDropZoneGrouping;

			// Update Absolutely-positioned children on Scroller (if applicable)
			// to fix Firefox b/c firefox uses position:absolute incorrectly
/*			if (qcodo.isBrowser(qcodo.FIREFOX) && (objControl.style.overflow == "auto"))
				objControl.onscroll = function(objEvent) {
					objEvent = qcodo.handleEvent(objEvent);
					for (var intIndex = 0; intIndex < this.childNodes.length; intIndex++) {
						if ((this.childNodes[intIndex].style) && (this.childNodes[intIndex].style.position == "absolute")) {
							if (!this.childNodes[intIndex].originalX) {
								this.childNodes[intIndex].originalX = this.childNodes[intIndex].offsetLeft;
								this.childNodes[intIndex].originalY = this.childNodes[intIndex].offsetTop;
							}

							this.childNodes[intIndex].style.left = this.childNodes[intIndex].originalX - this.scrollLeft + "px";
							this.childNodes[intIndex].style.top = this.childNodes[intIndex].originalY - this.scrollTop + "px";
						}
					}
				}*/
		}



		//////////////////////////////
		// Register Control - Moveable
		//////////////////////////////

		this.registerControlMoveable = function(mixControl) {
			var objControl; if (!(objControl = qcodo.getControl(mixControl))) return;
			var objWrapper = objControl.wrapper;

			objWrapper.moveable = true;
			
			// Control Handle and Mask
			objWrapper.mask = qcodo.getControl(objWrapper.id + "mask");
			if (!objWrapper.mask) {
				var objSpanElement = document.createElement('span');
				objSpanElement.id = objWrapper.id + "mask";
				objSpanElement.style.position = "absolute";
				document.getElementById("Qform__FormId").parentNode.appendChild(objSpanElement);
				objWrapper.mask = objSpanElement;
			}
			objWrapper.mask.wrapper = objWrapper;

			// Setup Mask
			objMask = objWrapper.mask
			objMask.style.position = "absolute";
			objMask.style.zIndex = 998;
			if (qcodo.isBrowser(qcodo.IE))
				objMask.style.filter = "alpha(opacity=50)";
			else
				objMask.style.opacity = 0.5;
			objMask.style.display = "none";
			objMask.innerHTML = "";

			objMask.handleAnimateComplete = function(mixControl) {
				this.style.display = "none";
			}
		}



		//////////////////////////////
		// Register Control - DropZone Target
		//////////////////////////////

		this.registerControlDropZoneTarget = function(mixControl) {
			var objControl; if (!(objControl = qcodo.getControl(mixControl))) return;
			var objWrapper = objControl.wrapper;

			// Control Handle and Mask
			objWrapper.dropZoneMask = qcodo.getControl(objWrapper.id + "dzmask");
			if (!objWrapper.dropZoneMask) {
				//<span id="%s_ctldzmask" style="position:absolute;"><span style="font-size: 1px">&nbsp;</span></span>
				var objSpanElement = document.createElement("span");
				objSpanElement.id = objWrapper.id + "dzmask";
				objSpanElement.style.position = "absolute";

				var objInnerSpanElement = document.createElement("span");
				objInnerSpanElement.style.fontSize = "1px";
				objInnerSpanElement.innerHTML = "&nbsp;"

				objSpanElement.appendChild(objInnerSpanElement);
				
				document.getElementById("Qform__FormId").parentNode.appendChild(objSpanElement);
				objWrapper.dropZoneMask = objSpanElement;

				objWrapper.dropZoneMask.wrapper = objWrapper;

				// Setup Mask
				objMask = objWrapper.dropZoneMask
				objMask.style.position = "absolute";
				objMask.style.top = "0px";
				objMask.style.left = "0px";
				objMask.style.borderColor = "#bb3399";
				objMask.style.borderStyle = "solid";
				objMask.style.borderWidth = "3px";
				objMask.style.display = "none";
			}
		}




		////////////////////////////////
		// Register Control - DropZone Grouping
		////////////////////////////////
		this.dropZoneGrouping = new Array();



		////////////////////////////////
		// Register Control - MoveHandle
		////////////////////////////////

		this.registerControlMoveHandle = function(mixControl) {				
			var objControl; if (!(objControl = qcodo.getControl(mixControl))) return;
			var objWrapper = objControl.wrapper;

			if (!objWrapper.handle) {
				// Control Handle and Mask
				objWrapper.handle = qcodo.getControl(objWrapper.id + "handle");
				objWrapper.handle.wrapper = objWrapper;
	
				var objHandle = objWrapper.handle;
				objHandle.style.width = objWrapper.offsetWidth;
				objHandle.style.height = objWrapper.offsetHeight;
				objHandle.style.cursor = "move";
				objHandle.style.zIndex = 999;
				objHandle.style.backgroundColor = "white";
				if (qcodo.isBrowser(qcodo.IE))
					objHandle.style.filter = "alpha(opacity=0)";
				else
					objHandle.style.opacity = 0.0;
				objHandle.style.top = objWrapper.offsetTop + "px";
				objHandle.style.left = objWrapper.offsetLeft + "px";
				objHandle.style.position = "absolute";
				objHandle.style.fontSize = "1px";
				objHandle.innerHTML = ".";
	
				// Assign Event Handlers
				document.onmousedown = qcodo.handleMouseDown;
				document.onmousemove = qcodo.handleMouseMove;
				document.onmouseup = qcodo.handleMouseUp;
	
				objWrapper.updateHandle = function() {
					var objHandle = this.handle;
					objHandle.style.width = objWrapper.offsetWidth;
					objHandle.style.height = objWrapper.offsetHeight;
	
					objWrapper.parentNode.appendChild(objHandle);
	
					objHandle.style.top = objWrapper.offsetTop + "px";
					objHandle.style.left = objWrapper.offsetLeft + "px";
				}

				// Setup Move Targets
				objWrapper.moveControls = new Object();
	
				objWrapper.registerMoveTarget = function(mixControl) {
					// If they pass in null, then register itself as the move target
					if (mixControl == null) mixControl = this.control;
	
					var objControl; if (!(objControl = qcodo.getControl(mixControl))) return;
					var objTargetWrapper = objControl.wrapper;
	
					if (objTargetWrapper)
						this.moveControls[objControl.id] = objTargetWrapper;
	//				this.registerDropZone(objTargetWrapper.parentNode);
				}
				
				objWrapper.regMT = objWrapper.registerMoveTarget;
	
				objWrapper.unregisterMoveTarget = function(mixControl) {
					var objControl; if (!(objControl = qcodo.getControl(mixControl))) return;
	
					if (objControl.id)
						this.moveControls[objControl.id] = null;
				}
	
				objWrapper.clearMoveTargets = function() {
					this.moveControls = new Object();
				}
	
				// Setup Drop Zones
				objWrapper.registerDropZone = function(mixControl) {
					var objControl; if (!(objControl = qcodo.getControl(mixControl))) return;
	
					if (objControl.wrapper) {
						qcodo.registerControlDropZoneTarget(objControl);
						this.dropControls[objControl.id] = objControl.wrapper;
					} else
						this.dropControls[objControl.id] = objControl;
				}

				objWrapper.regDZ = objWrapper.registerDropZone;
				
				objWrapper.unregisterDropZone = function(mixControl) {
					var objControl; if (!(objControl = qcodo.getControl(mixControl))) return;
	
					this.dropControls[objControl.id] = null;
				}
	
				objWrapper.clearDropZones = function() {
					this.dropControls = new Object();
				}
	
				objWrapper.clearDropZones();
				
				objWrapper.registerDropZoneGrouping = function(strGroupingId) {
					if (!qcodo.dropZoneGrouping[strGroupingId])
						qcodo.dropZoneGrouping[strGroupingId] = new Array();
					this.dropGroupings[strGroupingId] = true;
				}
				objWrapper.regDZG = objWrapper.registerDropZoneGrouping;
	
				objWrapper.clearDropZoneGroupings = function() {
					this.dropGroupings = new Object();
				}
				objWrapper.clearDropZoneGroupings();

				// Mouse Delta Calculator
				objWrapper.calculateMoveDelta = function() {
					// Calculate Move Delta
					var intDeltaX = qcodo.page.x - this.startDragX;
					var intDeltaY = qcodo.page.y - this.startDragY;
	
					intDeltaX = Math.min(Math.max(intDeltaX, -1 * this.boundingBox.x), qcodo.page.width - this.boundingBox.boundX);
					intDeltaY = Math.min(Math.max(intDeltaY, -1 * this.boundingBox.y), qcodo.page.height - this.boundingBox.boundY);
	
					return {x: intDeltaX, y: intDeltaY};
				}
	
				objWrapper.setupBoundingBox = function() {
					// Calculate moveControls aggregate bounding box (x,y,width,height,boundX,boundY)
					// Note that boundX is just (x + width), and boundY is just (y + height)
					var intMinX = null;
					var intMinY = null;
					var intMaxX = null;
					var intMaxY = null;
					for (var strKey in this.moveControls) {
						var objMoveControl = this.moveControls[strKey];
						var objAbsolutePosition = objMoveControl.getAbsolutePosition();
						if (intMinX == null) {
							intMinX = objAbsolutePosition.x;
							intMinY = objAbsolutePosition.y;
							intMaxX = objAbsolutePosition.x + objMoveControl.offsetWidth;
							intMaxY = objAbsolutePosition.y + objMoveControl.offsetHeight;
						} else {
							intMinX = Math.min(intMinX, objAbsolutePosition.x);
							intMinY = Math.min(intMinY, objAbsolutePosition.y);
							intMaxX = Math.max(intMaxX, objAbsolutePosition.x + objMoveControl.offsetWidth);
							intMaxY = Math.max(intMaxY, objAbsolutePosition.y + objMoveControl.offsetHeight);
						}
					}
	
					if (!this.boundingBox)
						this.boundingBox = new Object();
	
					this.boundingBox.x = intMinX;
					this.boundingBox.y = intMinY;
					this.boundingBox.boundX = intMaxX;
					this.boundingBox.boundY = intMaxY;
					this.boundingBox.width = intMaxX - intMinX;
					this.boundingBox.height = intMaxY - intMinY;
				}
	
				objWrapper.updateBoundingBox = function() {
					// Just like SETUP BoundingBox, except now we're using the MASKS instead of the Controls
					// (in case, becuase of hte move, the size of the control may have changed/been altered)
					var intMinX = null;
					var intMinY = null;
					var intMaxX = null;
					var intMaxY = null;
					for (var strKey in this.moveControls) {
						var objMoveControl = this.moveControls[strKey];
						var objAbsolutePosition = objMoveControl.getAbsolutePosition();
						if (intMinX == null) {
							intMinX = objAbsolutePosition.x;
							intMinY = objAbsolutePosition.y;
							intMaxX = objAbsolutePosition.x + objMoveControl.mask.offsetWidth;
							intMaxY = objAbsolutePosition.y + objMoveControl.mask.offsetHeight;
						} else {
							intMinX = Math.min(intMinX, objAbsolutePosition.x);
							intMinY = Math.min(intMinY, objAbsolutePosition.y);
							intMaxX = Math.max(intMaxX, objAbsolutePosition.x + objMoveControl.mask.offsetWidth);
							intMaxY = Math.max(intMaxY, objAbsolutePosition.y + objMoveControl.mask.offsetHeight);
						}
					}
	
					this.boundingBox.x = intMinX;
					this.boundingBox.y = intMinY;
					this.boundingBox.boundX = intMaxX;
					this.boundingBox.boundY = intMaxY;
					this.boundingBox.width = intMaxX - intMinX;
					this.boundingBox.height = intMaxY - intMinY;
				}
	
				objWrapper.moveMasks = function() {
					// Calculate Move Delta
					var objMoveDelta = this.calculateMoveDelta();
					var intDeltaX = objMoveDelta.x;
					var intDeltaY = objMoveDelta.y;
	
					var blnValidDropZone = this.validateDropZone();
					if (blnValidDropZone)
						this.handle.style.cursor = "url(" + qcodo.includesPath + "/qform/assets/move_drop.cur), auto";
					else
						this.handle.style.cursor = "url(" + qcodo.includesPath + "/qform/assets/move_nodrop.cur), auto";
	
					// Update Everything that's Moving (e.g. all controls in qcodo.moveControls)
					for (var strKey in this.moveControls) {
						var objWrapper = this.moveControls[strKey];
						var objMask = objWrapper.mask;
	
						// Fixes a weird Firefox bug
						if (objMask.innerHTML == "")
							objMask.innerHTML = ".";
						if (objMask.innerHTML = ".")
							objMask.innerHTML = objWrapper.innerHTML.replace(' id="', ' ixdx="');
	
						// Recalculate Widths
						this.updateBoundingBox();
	
						// Move this control's mask
						objWrapper.setMaskOffset(intDeltaX, intDeltaY);
	
						if (blnValidDropZone) {
							objMask.style.cursor = "url(" + qcodo.includesPath + "/qform/assets/move_drop.cur), auto";
						} else {
							objMask.style.cursor = "url(" + qcodo.includesPath + "/qform/assets/move_nodrop.cur), auto";
						}
					}
				}

				objWrapper.getDropZoneControlWrappers = function() {
					var arrayToReturn = new Array();
					
					for (var strDropKey in this.dropControls) {
						var objDropWrapper = this.dropControls[strDropKey];
						if (objDropWrapper)
							arrayToReturn[strDropKey] = objDropWrapper;
					}
					
					for (var strGroupingId in this.dropGroupings) {
						if (this.dropGroupings[strGroupingId]) for (var strControlId in qcodo.dropZoneGrouping[strGroupingId]) {
							if (strControlId.substring(0, 1) != "_") {
								var objDropWrapper = qcodo.dropZoneGrouping[strGroupingId][strControlId];
								if (objDropWrapper) {
									if (objDropWrapper.control.id == objWrapper.control.id) {
										if (qcodo.dropZoneGrouping[strGroupingId]["__allowSelf"])
											arrayToReturn[strControlId] = objDropWrapper;
									} else if (objDropWrapper.control.id == objWrapper.parentNode.id) {
										if (qcodo.dropZoneGrouping[strGroupingId]["__allowSelfParent"])
											arrayToReturn[strControlId] = objDropWrapper;
									} else {
										arrayToReturn[strControlId] = objDropWrapper;
									}
								}
							}
						}
					}
					return arrayToReturn;
				}

				objWrapper.validateDropZone = function() {
					var blnFoundTarget = false;
					var blnFormOkay = false;
					var dropControls = this.getDropZoneControlWrappers();

					for (var strDropKey in dropControls) {
						var objDropWrapper = dropControls[strDropKey];
						if (objDropWrapper) {
							if (objDropWrapper.nodeName.toLowerCase() == 'form') {
								blnFormOkay = true;
							} else if (objDropWrapper.containsPoint(qcodo.page.x, qcodo.page.y)) {
								if (blnFoundTarget) {
									objDropWrapper.dropZoneMask.style.display = "none";
								} else {
									objDropWrapper.dropZoneMask.style.display = "block";
									var objAbsolutePosition = objDropWrapper.getAbsolutePosition();
									if (qcodo.isBrowser(qcodo.IE)) {
										objDropWrapper.dropZoneMask.style.width = Math.max(7, objDropWrapper.control.offsetWidth);
										objDropWrapper.dropZoneMask.style.height = Math.max(7, objDropWrapper.control.offsetHeight);

//										if (objDropWrapper.style.position == 'absolute') {
											var objAbsolutePosition = objDropWrapper.getAbsolutePosition();
//											objDropWrapper.setDropZoneMaskAbsolutePosition(objAbsolutePosition.x + 10, objAbsolutePosition.y + 10);
											objDropWrapper.setDropZoneMaskAbsolutePosition(objAbsolutePosition.x, objAbsolutePosition.y);
//										}
									} else {
										objDropWrapper.dropZoneMask.style.width = Math.max(1, objDropWrapper.control.offsetWidth - 6);
										objDropWrapper.dropZoneMask.style.height = Math.max(1, objDropWrapper.control.offsetHeight - 6);

//										if (objDropWrapper.style.position != 'absolute') {
											var objAbsolutePosition = objDropWrapper.getAbsolutePosition();
											objDropWrapper.setDropZoneMaskAbsolutePosition(objAbsolutePosition.x, objAbsolutePosition.y);
//										}
									}
									blnFoundTarget = true;
								}
							} else {
								objDropWrapper.dropZoneMask.style.display = "none";
							}
						}
					}
	
					return (blnFoundTarget || blnFormOkay);
				}
	
				// Will return "NULL" if there was no target found
				// Could also return the Form if not dropped on any valid target BUT tbe Form is still a drop zone
				objWrapper.getDropTarget = function() {
					var objForm = null;
					var objToReturn = null;
					
					var dropControls = this.getDropZoneControlWrappers();
					
					for (var strDropKey in dropControls) {
						var objDropWrapper = dropControls[strDropKey];
						if (objDropWrapper) {
							if (objDropWrapper.nodeName.toLowerCase() == 'form')
								objForm = objDropWrapper;
							else if (objDropWrapper.containsPoint(qcodo.page.x, qcodo.page.y)) {
								objDropWrapper.dropZoneMask.style.display = "none";
								if (!objToReturn)
									objToReturn = objDropWrapper;
							}
						}
					}
	
					if (objToReturn)
						return objToReturn;

					if (objForm)
						return objForm;
	
					return null;
				}
	
				objWrapper.resetMasks = function(intDeltaX, intDeltaY, intSpeed) {
					qcodo.moveHandleReset = this;
	
					if (intDeltaX || intDeltaY) {
						this.resetCurrentOffsetX = intDeltaX * 1.0;
						this.resetCurrentOffsetY = intDeltaY * 1.0;
	
						var fltTotalMove = Math.sqrt(Math.pow(intDeltaX, 2) + Math.pow(intDeltaY, 2));
						var fltRatio = (intSpeed * 1.0) / fltTotalMove;
						this.resetStepX = fltRatio * intDeltaX;
						this.resetStepY = fltRatio * intDeltaY;
	
						qcodo.setTimeout("move_mask_return", "qcodo.getControl('" + this.id + "').resetMaskHelper()", 10);
					}
				}
	
				objWrapper.resetMaskHelper = function() {
					if (this.resetCurrentOffsetX < 0)
						this.resetCurrentOffsetX = Math.min(this.resetCurrentOffsetX - this.resetStepX, 0);
					else
						this.resetCurrentOffsetX = Math.max(this.resetCurrentOffsetX - this.resetStepX, 0);
	
					if (this.resetCurrentOffsetY < 0)
						this.resetCurrentOffsetY = Math.min(this.resetCurrentOffsetY - this.resetStepY, 0);
					else
						this.resetCurrentOffsetY = Math.max(this.resetCurrentOffsetY - this.resetStepY, 0);
	
					for (var strKey in this.moveControls) {
						var objWrapper = this.moveControls[strKey];
						objWrapper.setMaskOffset(this.resetCurrentOffsetX, this.resetCurrentOffsetY);
	
						if ((this.resetCurrentOffsetX == 0) && (this.resetCurrentOffsetY == 0)) {
							objWrapper.mask.style.display = "none";
						}
					}
	
					if ((this.resetCurrentOffsetX != 0) || (this.resetCurrentOffsetY != 0))
						qcodo.setTimeout("move_mask_return", "qcodo.getControl('" + this.id + "').resetMaskHelper()", 10);
					else
						qcodo.moveHandleReset = null;
				}
	
				objWrapper.resetMasksCancel = function() {
					qcodo.clearTimeout("move_mask_return");
					qcodo.moveHandleReset = null;
					for (var strKey in this.moveControls) {
						var objWrapper = this.moveControls[strKey];
						objWrapper.mask.style.display = "none";
					}
				}

/*				// Specifically for Microsoft IE
				if (objHandle.setCapture) {
					objHandle.onmouseover = function() {
						objHandle.setCapture()
					}

					objHandle.onmouseout = function() {
						objHandle.releaseCapture()
					}
				}*/
			}
		}


		this.animateMove = function(mixControl, intDestinationX, intDestinationY, intSpeed) {
			var objControl; if (!(objControl = qcodo.getControl(mixControl))) return;

			// Record Destination Coordinates
			objControl.destinationX = intDestinationX;
			objControl.destinationY = intDestinationY;

			// Get Starting Coordinates
			var objAbsolutePosition = qcodo.getAbsolutePosition(objControl);
			objControl.currentX = objAbsolutePosition.x * 1.0;
			objControl.currentY = objAbsolutePosition.y * 1.0;

			// Calculate the amount to move in the X- and Y- direction per step
			var fltTotalMove = Math.sqrt(Math.pow(objControl.destinationY - objControl.currentY, 2) + Math.pow(objControl.destinationX - objControl.currentX, 2));
			var fltTotalMoveX = (objControl.destinationX * 1.0) - objControl.currentX;
			var fltTotalMoveY = (objControl.destinationY * 1.0) - objControl.currentY;
			objControl.stepMoveX = ((intSpeed * 1.0) / fltTotalMove) * fltTotalMoveX;
			objControl.stepMoveY = ((intSpeed * 1.0) / fltTotalMove) * fltTotalMoveY;

			qcodo.setTimeout(objControl, "qcodo.handleAnimateMove('" + objControl.id + "');", 10);
		}

		this.handleAnimateMove = function(mixControl) {
			var objControl; if (!(objControl = qcodo.getControl(mixControl))) return;

			// Update Current Coordinates
			if (objControl.stepMoveX < 0)
				objControl.currentX = Math.max(objControl.destinationX, objControl.currentX + objControl.stepMoveX);
			else
				objControl.currentX = Math.min(objControl.destinationX, objControl.currentX + objControl.stepMoveX);

			if (objControl.stepMoveY < 0)
				objControl.currentY = Math.max(objControl.destinationY, objControl.currentY + objControl.stepMoveY);
			else
				objControl.currentY = Math.min(objControl.destinationY, objControl.currentY + objControl.stepMoveY);

			qcodo.setAbsolutePosition(objControl, Math.round(objControl.currentX), Math.round(objControl.currentY));
			
			if ((Math.round(objControl.currentX) == objControl.destinationX) &&
				(Math.round(objControl.currentY) == objControl.destinationY)) {
				// We are done
				
				if (objControl.handleAnimateComplete)
					objControl.handleAnimateComplete(objControl);
			} else {
				// Do it again
				qcodo.setTimeout(objControl, "qcodo.handleAnimateMove('" + objControl.id + "');", 10);
			}
		}


		////////////////////////////////////////////
		// Initialize: Timers-related functionality
		////////////////////////////////////////////

		this._objTimers = new Object();

		this.clearTimeout = function(strTimerId) {
			if (qcodo._objTimers[strTimerId]) {
				clearTimeout(qcodo._objTimers[strTimerId]);
				qcodo._objTimers[strTimerId] = null;
			}
		}

		this.setTimeout = function(strTimerId, strAction, intDelay) {
			qcodo.clearTimeout(strTimerId);
			qcodo._objTimers[strTimerId] = setTimeout(strAction, intDelay);
		}

		////////////////////////////////////////////
		// Initialize: System-related functionality
		////////////////////////////////////////////

		this.handleEvent = function(objEvent) {
			objEvent = (objEvent) ? objEvent : ((typeof(event) == "object") ? event : null);

			if (objEvent) {
				if (typeof(objEvent.clientX) != "undefined") {
					if (qcodo.isBrowser(qcodo.SAFARI)) {
						qcodo.mouse.x = objEvent.clientX - window.document.body.scrollLeft;
						qcodo.mouse.y = objEvent.clientY - window.document.body.scrollTop;
						qcodo.client.x = objEvent.clientX - window.document.body.scrollLeft;
						qcodo.client.y = objEvent.clientY - window.document.body.scrollTop;
					} else {
						qcodo.mouse.x = objEvent.clientX;
						qcodo.mouse.y = objEvent.clientY;
						qcodo.client.x = objEvent.clientX;
						qcodo.client.y = objEvent.clientY;
					}
				}

				if (qcodo.isBrowser(qcodo.IE)) {
					qcodo.mouse.left = ((objEvent.button & 1) ? true : false);
					qcodo.mouse.right = ((objEvent.button & 2) ? true : false);
					qcodo.mouse.middle = ((objEvent.button & 4) ? true : false);
				} else if (qcodo.isBrowser(qcodo.SAFARI)) {
					qcodo.mouse.left = ((objEvent.button && !objEvent.ctrlKey) ? true : false);
					qcodo.mouse.right = ((objEvent.button && objEvent.ctrlKey) ? true : false);
					qcodo.mouse.middle = false;
				} else {
					qcodo.mouse.left = (objEvent.button == 0);
					qcodo.mouse.right = (objEvent.button == 2);
					qcodo.mouse.middle = (objEvent.button == 1);
				}

				qcodo.key.alt = (objEvent.altKey) ? true : false;
				qcodo.key.control = (objEvent.ctrlKey) ? true : false;
				qcodo.key.shift = (objEvent.shiftKey) ? true : false;
				qcodo.key.code = (objEvent.keyCode) ? (objEvent.keyCode) : 0;
				
				if (objEvent.originalTarget)
					qcodo.target = objEvent.originalTarget;
				else if (objEvent.srcElement)
					qcodo.target = objEvent.srcElement;
				else
					qcodo.target = null;
			}

			qcodo.client.width = (qcodo.isBrowser(qcodo.SAFARI)) ? window.innerWidth : window.document.body.clientWidth;
			qcodo.client.height = (qcodo.isBrowser(qcodo.SAFARI)) ? window.innerHeight: window.document.body.clientHeight;

			qcodo.page.x = qcodo.mouse.x + qcodo.scroll.x;
			qcodo.page.y = qcodo.mouse.y + qcodo.scroll.y;

			qcodo.page.width = Math.max(window.document.body.scrollWidth, qcodo.client.width);
			qcodo.page.height = Math.max(window.document.body.scrollHeight, qcodo.client.height);

			qcodo.scroll.x = window.scrollX || window.document.body.scrollLeft;
			qcodo.scroll.y = window.scrollY || window.document.body.scrollTop;

			qcodo.scroll.width = window.document.body.scrollWidth - qcodo.client.width;
			qcodo.scroll.height = window.document.body.scrollHeight - qcodo.client.height;

			return objEvent;
		}

		this.key = {
			control: false,
			alt: false,
			shift: false,
			code: null
		}

		this.mouse = {
			x: 0,
			y: 0,
			left: false,
			middle: false,
			right: false
		}

		this.client = {
			x: null,
			y: null,
			width: null,
			height: null
//			width: (this.isBrowser(this.IE)) ? window.document.body.clientWidth : window.innerWidth,
//			height: (this.isBrowser(this.IE)) ? window.document.body.clientHeight : window.innerHeight
		}

		this.page = {
			x: null,
			y: null,
			width: null,
			height: null
//			width: window.document.body.scrollWidth,
//			height: window.document.body.scrollHeight
		}

		this.scroll = {
//			x: null,
//			y: null,
			x: window.scrollX || window.document.body.scrollLeft,
			y: window.scrollY || window.document.body.scrollTop,
//			width: null,
//			height: null
			width: window.document.body.scrollWidth - this.client.width,
			height: window.document.body.scrollHeight - this.client.height
		}




		this.terminateEvent = function(objEvent) {
			objEvent = qcodo.handleEvent(objEvent);

			if (objEvent) {
				// Stop Propogation
				if (objEvent.preventDefault)
					objEvent.preventDefault();
				if (objEvent.stopPropagation)
					objEvent.stopPropagation();
				objEvent.cancelBubble = true;
				objEvent.returnValue = false;
			}

			return false;
		}

		this.handleMouseDown = function(objEvent) {
			objEvent = qcodo.handleEvent(objEvent);

			var objHandle = qcodo.target;
			if (!objHandle) return true;

			var objWrapper = objHandle.wrapper;
			if (!objWrapper) return true;

			// Check for Move
			if (qcodo.mouse.left) {					
				// See if this objControl moves a control of any kind
				if (!objWrapper.moveControls)
					return true;
					
				qcodo.moveControls = objWrapper.moveControls;
				qcodo.moveHandle = objWrapper;

				// Specifically for Microsoft IE
				if (objHandle.setCapture) {
					objHandle.setCapture()
				}

				objHandle.onmouseout = null;
				if (document.selection)
					document.selection.empty();

				// Set the Handle's MoveControls Bounding Box
				objWrapper.setupBoundingBox();

				// Calculate the offset (the top-left page coordinates of the bounding box vs. where the mouse is on the page)
				objWrapper.offsetX = qcodo.page.x - objWrapper.boundingBox.x;
				objWrapper.offsetY = qcodo.page.y - objWrapper.boundingBox.y;
				objWrapper.startDragX = qcodo.page.x;
				objWrapper.startDragY = qcodo.page.y;

				// Clear MaskReturn Timeout (if applicable)
				if (qcodo.moveHandleReset)
					qcodo.moveHandleReset.resetMasksCancel();

				// Make the Masks appear (if applicable)
				for (var strKey in objWrapper.moveControls) {
					var objMoveControl = objWrapper.moveControls[strKey];
					var objMask = objMoveControl.mask

					var objAbsolutePosition = objMoveControl.getAbsolutePosition();

					objMask.style.display = "block";
					objMask.style.top = objAbsolutePosition.x;
					objMask.style.left = objAbsolutePosition.y;
					objMask.innerHTML = "";
				}

				return qcodo.terminateEvent(objEvent);
			}

			return true;
		}

		this.handleMouseMove = function(objEvent) {
			objEvent = qcodo.handleEvent(objEvent);

			// Bug Fix for IE -- if the mouse button is NOT down, and if we are currently dragging something
//			if (qcodo.isBrowser(qcodo.IE) && !qcodo.mouse.left && qcodo.moveHandle) {
//				var objNewEvent = new Object();
//				objNewEvent.clientX = document.objDragMask.objMirror.offsetLeft + document.objDragMask.intOffsetX;
//				objNewEvent.clientY = document.objDragMask.objMirror.offsetTop + document.objDragMask.intOffsetY;
//				Qform__HandleMouseUp(objNewEvent);
//				return;
//			}

			if (qcodo.moveHandle) {
				var objHandle = qcodo.moveHandle;

				// In case IE accidentally marks a selection...
				if (document.selection)
					document.selection.empty();

				// Do We Scroll?
				if ((qcodo.client.x <= 30) || (qcodo.client.y >= (qcodo.client.height - 30)) ||
					(qcodo.client.y <= 30) || (qcodo.client.x >= (qcodo.client.width - 30))) {
					qcodo.handleScroll();
				} else {
					// Clear Handle Timeout
					qcodo.clearTimeout(objHandle.id);
					
					objHandle.moveMasks();
				}

				return qcodo.terminateEvent(objEvent);
			}

			return true;
		}

		this.handleMouseUp = function(objEvent) {
			objEvent = qcodo.handleEvent(objEvent);

			if (qcodo.moveHandle) {
				var objHandle = qcodo.moveHandle;

				// Calculate Move Delta
				var objMoveDelta = objHandle.calculateMoveDelta();
				var intDeltaX = objMoveDelta.x;
				var intDeltaY = objMoveDelta.y;

				// In case IE accidentally marks a selection...
				if (document.selection)
					document.selection.empty();

				// For IE to release release/setCapture
				if (objHandle.handle.releaseCapture) {
					objHandle.handle.releaseCapture();
					objHandle.handle.onmouseout = function() {this.releaseCapture()};
				}
				
				// Stop Scrolling
				qcodo.clearTimeout(objHandle.id);

				// Validate Drop Zone
				var objDropControl;

				if ((intDeltaX == 0) && (intDeltaY == 0)) {
					// Nothing Moved!
					objDropControl = null;
				} else {
					objDropControl = objHandle.getDropTarget();
				}

				if (objDropControl) {
					objHandle.handle.style.cursor = "move";

					// Update everything that's moving (e.g. all controls in qcodo.moveControls)
					for (var strKey in objHandle.moveControls) {
						var objWrapper = objHandle.moveControls[strKey];
						var objMask = objWrapper.mask;

						objMask.style.display = "none";
						objMask.style.cursor = null;
//						qcodo.moveControls[strKey] = null;

						objWrapper.updateStyle("position", "absolute");

						// Get Control's Position
						var objAbsolutePosition = objWrapper.getAbsolutePosition();

						// Update Parent -- Wrapper now belongs to a new DropControl
						if (objDropControl.nodeName.toLowerCase() == 'form') {
							if (objWrapper.parentNode != objDropControl)
								objWrapper.updateStyle("parent", objDropControl.id);
						} else {
							if (objDropControl.id != objWrapper.parentNode.parentNode.id)
								objWrapper.updateStyle("parent", objDropControl.control.id);
						}

						// Update Control's Position
						objWrapper.setAbsolutePosition(objAbsolutePosition.x + intDeltaX, objAbsolutePosition.y + intDeltaY, true);

						if (objWrapper.updateHandle)
							objWrapper.updateHandle();

						// Setup OnMove (if applicable)
						if (objWrapper.control.getAttribute("onqcodomove")) {
//							if (qcodo.isBrowser(qcodo.IE)) {
//								objWrapper.control.onmove = objWrapper.control.getAttribute("onmove");
//								objWrapper.control.onmove();

//								objWrapper.control.movecommand = function(strOnMoveCommand) {
//									alert('Attempting: ' + strOnMoveCommand);
//									eval(strOnMoveCommand);
//								}
//								objWrapper.control.movecommand(objWrapper.control.getAttribute("onmove"));
//							} else {
								objWrapper.control.qcodomove = function(strOnMoveCommand) {
									eval(strOnMoveCommand);
								}
								objWrapper.control.qcodomove(objWrapper.control.getAttribute("onqcodomove"));
//							}
						}
					}

					qcodo.moveHandle = null;
					qcodo.moveControls = null;
				} else {
					// Rejected
					qcodo.moveHandle = null;
					objHandle.handle.style.cursor = "move";

					for (var strKey in qcodo.moveControls) {
						var objWrapper = qcodo.moveControls[strKey];
						var objMask = objWrapper.mask;

						objMask.style.cursor = null;
					}

					if (qcodo.isBrowser(this.IE))
						objHandle.resetMasks(intDeltaX, intDeltaY, 25);
					else
						objHandle.resetMasks(intDeltaX, intDeltaY, 50);
				}

				if ((intDeltaX == 0) && (intDeltaY == 0)) {
					if (objHandle.control.onclick)
						objHandle.control.onclick(objEvent);
				} else {
					return qcodo.terminateEvent(objEvent);
				}
			}

			return;
		}
		
		
		this.handleScroll = function() {
			var objHandle = qcodo.moveHandle;

			// Clear Timeout
			qcodo.clearTimeout(objHandle.id);

			// How much to scroll by
			var intScrollByX = 0;
			var intScrollByY = 0;

			// Calculate our ScrollByY amount
			if (qcodo.client.y <= 30) {
				var intDivisor = (qcodo.isBrowser(qcodo.IE)) ? 1.5 : 3;
				intScrollByY = Math.round((qcodo.client.y - 30) / intDivisor);
			} else if (qcodo.client.y >= (qcodo.client.height - 30)) {
				var intDivisor = (qcodo.isBrowser(qcodo.IE)) ? 1.5 : 3;
				intScrollByY = Math.round((qcodo.client.y - (qcodo.client.height - 30)) / intDivisor);
			}

			// Calculate our ScrollByX amount
			if (qcodo.client.x <= 30) {
				var intDivisor = (qcodo.isBrowser(qcodo.IE)) ? 1 : 2;
				intScrollByX = Math.round((qcodo.client.x - 30) / intDivisor);
			} else if (qcodo.client.x >= (qcodo.client.width - 30)) {
				var intDivisor = (qcodo.isBrowser(qcodo.IE)) ? 1 : 2;
				intScrollByX = Math.round((qcodo.client.x - (qcodo.client.width - 30)) / intDivisor);
			}

			// Limit ScrollBy amounts (dependent on current scroll and scroll.max's)
			if (intScrollByX < 0) {
				// Scroll to Left
				intScrollByX = Math.max(intScrollByX, 0 - qcodo.scroll.x);
			} else if (intScrollByX > 0) {
				// Scroll to Right
				intScrollByX = Math.min(intScrollByX, qcodo.scroll.width - qcodo.scroll.x);
			}
			if (intScrollByY < 0) {
				// Scroll to Left
				intScrollByY = Math.max(intScrollByY, 0 - qcodo.scroll.y);
			} else if (intScrollByY > 0) {
				// Scroll to Right
				intScrollByY = Math.min(intScrollByY, qcodo.scroll.height - qcodo.scroll.y);
			}

			// Perform the Scroll
			window.scrollBy(intScrollByX, intScrollByY);

			// Update Event Stats
			qcodo.handleEvent(null);

			// Update Handle Offset
			objHandle.offsetX -= intScrollByX;
			objHandle.offsetY -= intScrollByY;

			objHandle.moveMasks();
			if (intScrollByX || intScrollByY)
				qcodo.setTimeout(objHandle.id, "qcodo.handleScroll()", 25);
		}



		////////////////////////////////////////////
		// Initialize: Logging-related functionality
		////////////////////////////////////////////

		this.logMessage = function(strMessage, blnReset, blnNonEscape) {
			var objLogger = qcodo.getControl("Qform_Logger");

			if (!objLogger) {
				var objLogger = document.createElement("div");
				objLogger.id = "Qform_Logger";
				objLogger.style.display = "none";
				objLogger.style.width = "400px";
				objLogger.style.backgroundColor = "#dddddd";
				objLogger.style.fontSize = "10px";
				objLogger.style.fontFamily = "lucida console, courier, monospaced";
				objLogger.style.padding = "6px";
				objLogger.style.overflow = "auto";

				if (qcodo.isBrowser(qcodo.IE))
					objLogger.style.filter = "alpha(opacity=50)";
				else
					objLogger.style.opacity = 0.5;

				document.body.appendChild(objLogger);
			}

			if (!blnNonEscape)
				strMessage = strMessage.replace(/</g, '&lt;');

			var strPosition = "fixed";
			var strTop = "0px";
			var strLeft = "0px";
			if (qcodo.isBrowser(qcodo.IE)) {
				// IE doesn't support position:fixed, so manually set positioning
				strPosition = "absolute";
				strTop = qcodo.scroll.x + "px";
				strLeft = qcodo.scroll.y + "px";
			}

			objLogger.style.position = strPosition;
			objLogger.style.top = strTop;
			objLogger.style.left = strLeft;
			objLogger.style.height = qcodo.client.height;
			objLogger.style.display = 'inline';

			var strHeader = '<a href="javascript:qcodo.logRemove()">Remove</a><br/><br/>';

			if (blnReset)
				objLogger.innerHTML = strHeader + strMessage + "<br/>";
			else if (objLogger.innerHTML == "")
				objLogger.innerHTML = strHeader + strMessage + "<br/>";
			else
				objLogger.innerHTML += strMessage + "<br/>";
		}

		this.logRemove = function() {
			var objLogger = qcodo.getControl('Qform_Logger');
			if (objLogger)
				objLogger.style.display = 'none';
		}

		this.logEventStats = function(objEvent) {
			objEvent = qcodo.handleEvent(objEvent);

			var strMessage = "";
			strMessage += "scroll (x, y): " + qcodo.scroll.x + ", " + qcodo.scroll.y + "<br/>";
			strMessage += "scroll (width, height): " + qcodo.scroll.width + ", " + qcodo.scroll.height + "<br/>";
			strMessage += "client (x, y): " + qcodo.client.x + ", " + qcodo.client.y + "<br/>";
			strMessage += "client (width, height): " + qcodo.client.width + ", " + qcodo.client.height + "<br/>";
			strMessage += "page (x, y): " + qcodo.page.x + ", " + qcodo.page.y + "<br/>";
			strMessage += "page (width, height): " + qcodo.page.width + ", " + qcodo.page.height + "<br/>";
			strMessage += "mouse (x, y): " + qcodo.mouse.x + ", " + qcodo.mouse.y + "<br/>";
			strMessage += "mouse (left, middle, right): " + qcodo.mouse.left + ", " + qcodo.mouse.middle + ", " + qcodo.mouse.right + "<br/>";
			strMessage += "key (alt, shift, control, code): " + qcodo.key.alt + ", " + qcodo.key.shift + ", " +
				qcodo.key.control + ", " + qcodo.key.code;

			qcodo.logMessage("Event Stats", true);
			qcodo.logMessage(strMessage);
		}

		this.logObject = function(objObject) {
			var strDump = "";

			for (var strKey in objObject) {
				var strData = objObject[strKey];

				strDump += strKey + ": ";
				if (typeof strData == 'function')
					strDump += "&lt;FUNCTION&gt;";
				else if ((strKey == 'outerText') || (strKey == 'innerText') || (strKey == 'outerHTML') || (strKey == 'innerHTML'))
					strDump += "&lt;TEXT&gt;";
				else
					strDump += strData;
				strDump += "<br/>";
			}

			qcodo.logMessage("Object Stats", true);
			qcodo.logMessage(strDump, false, true);
		}

		// Shortcuts
		this.getC = this.getControl;
		this.getW = this.getWrapper;
		this.regC = this.registerControl;
		this.regCM = this.registerControlMoveable;
		this.regCMH = this.registerControlMoveHandle;
	}
}

// QC Shortcut
var qc = qcodo;

qc.initialize();