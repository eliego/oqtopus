
		function treenavToggleImage(strControlId) {
			var blnShow = treenavToggleDisplay(strControlId + "_sub", null, "block");
			
			var objImage = document.getElementById(strControlId + "_image");
			var strPath = qc.includesPath + "/qform/assets/treenav_expanded.png";
			var strPathNotExpanded = qc.includesPath + "/qform/assets/treenav_not_expanded.png";

			if (blnShow)
				objImage.src = strPath;
			else
				objImage.src = strPathNotExpanded;

			qcodo.recordControlModification(strControlId, 'Expanded', (blnShow) ? '1' : '0');
		}

		function treenavToggleDisplay(mixControl, strShowOrHide, strDisplayStyle) {
			// Toggles the display/hiding of the entire control (including any design/wrapper HTML)
			// If ShowOrHide is blank, then we toggle
			// Otherwise, we'll execute a "show" or a "hide"
			var objControl; if (!(objControl = qcodo.getControl(mixControl))) return;

			if (strShowOrHide) {
				if (strShowOrHide == "show") {
					objControl.style.display = strDisplayStyle;
					return true;
				} else {
					objControl.style.display = "none";
					return false;
				}
			} else {
				if (objControl.style.display == "none") {
					objControl.style.display = strDisplayStyle;
					return true;
				} else {
					objControl.style.display = "none";
					return false;
				}
			}
		}