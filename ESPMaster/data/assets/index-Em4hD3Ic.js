(function(){const e=document.createElement("link").relList;if(e&&e.supports&&e.supports("modulepreload"))return;for(const n of document.querySelectorAll('link[rel="modulepreload"]'))o(n);new MutationObserver(n=>{for(const r of n)if(r.type==="childList")for(const c of r.addedNodes)c.tagName==="LINK"&&c.rel==="modulepreload"&&o(c)}).observe(document,{childList:!0,subtree:!0});function t(n){const r={};return n.integrity&&(r.integrity=n.integrity),n.referrerPolicy&&(r.referrerPolicy=n.referrerPolicy),n.crossOrigin==="use-credentials"?r.credentials="include":n.crossOrigin==="anonymous"?r.credentials="omit":r.credentials="same-origin",r}function o(n){if(n.ep)return;n.ep=!0;const r=t(n);fetch(n.href,r)}})();var I,v,de,P,_e,pe,R,Q,j,z,C={},he=[],Se=/acit|ex(?:s|g|n|p|$)|rph|grid|ows|mnc|ntw|ine[ch]|zoo|^ord|itera/i,X=Array.isArray;function $(_,e){for(var t in e)_[t]=e[t];return _}function ve(_){var e=_.parentNode;e&&e.removeChild(_)}function $e(_,e,t){var o,n,r,c={};for(r in e)r=="key"?o=e[r]:r=="ref"?n=e[r]:c[r]=e[r];if(arguments.length>2&&(c.children=arguments.length>3?I.call(arguments,2):t),typeof _=="function"&&_.defaultProps!=null)for(r in _.defaultProps)c[r]===void 0&&(c[r]=_.defaultProps[r]);return U(_,c,o,n,null)}function U(_,e,t,o,n){var r={type:_,props:e,key:t,ref:o,__k:null,__:null,__b:0,__e:null,__d:void 0,__c:null,constructor:void 0,__v:n??++de,__i:-1,__u:0};return n==null&&v.vnode!=null&&v.vnode(r),r}function B(_){return _.children}function W(_,e){this.props=_,this.context=e}function H(_,e){if(e==null)return _.__?H(_.__,_.__i+1):null;for(var t;e<_.__k.length;e++)if((t=_.__k[e])!=null&&t.__e!=null)return t.__e;return typeof _.type=="function"?H(_):null}function me(_){var e,t;if((_=_.__)!=null&&_.__c!=null){for(_.__e=_.__c.base=null,e=0;e<_.__k.length;e++)if((t=_.__k[e])!=null&&t.__e!=null){_.__e=_.__c.base=t.__e;break}return me(_)}}function te(_){(!_.__d&&(_.__d=!0)&&P.push(_)&&!M.__r++||_e!==v.debounceRendering)&&((_e=v.debounceRendering)||pe)(M)}function M(){var _,e,t,o,n,r,c,u;for(P.sort(R);_=P.shift();)_.__d&&(e=P.length,o=void 0,r=(n=(t=_).__v).__e,c=[],u=[],t.__P&&((o=$({},n)).__v=n.__v+1,v.vnode&&v.vnode(o),Y(t.__P,o,n,t.__n,t.__P.namespaceURI,32&n.__u?[r]:null,c,r??H(n),!!(32&n.__u),u),o.__v=n.__v,o.__.__k[o.__i]=o,be(c,o,u),o.__e!=r&&me(o)),P.length>e&&P.sort(R));M.__r=0}function ye(_,e,t,o,n,r,c,u,f,l,d){var i,p,s,g,x,b=o&&o.__k||he,h=e.length;for(t.__d=f,Pe(t,e,b),f=t.__d,i=0;i<h;i++)(s=t.__k[i])!=null&&typeof s!="boolean"&&typeof s!="function"&&(p=s.__i===-1?C:b[s.__i]||C,s.__i=i,Y(_,s,p,n,r,c,u,f,l,d),g=s.__e,s.ref&&p.ref!=s.ref&&(p.ref&&Z(p.ref,null,s),d.push(s.ref,s.__c||g,s)),x==null&&g!=null&&(x=g),65536&s.__u||p.__k===s.__k?(f&&!f.isConnected&&(f=H(p)),f=ge(s,f,_)):typeof s.type=="function"&&s.__d!==void 0?f=s.__d:g&&(f=g.nextSibling),s.__d=void 0,s.__u&=-196609);t.__d=f,t.__e=x}function Pe(_,e,t){var o,n,r,c,u,f=e.length,l=t.length,d=l,i=0;for(_.__k=[],o=0;o<f;o++)c=o+i,(n=_.__k[o]=(n=e[o])==null||typeof n=="boolean"||typeof n=="function"?null:typeof n=="string"||typeof n=="number"||typeof n=="bigint"||n.constructor==String?U(null,n,null,null,null):X(n)?U(B,{children:n},null,null,null):n.constructor===void 0&&n.__b>0?U(n.type,n.props,n.key,n.ref?n.ref:null,n.__v):n)!=null?(n.__=_,n.__b=_.__b+1,u=He(n,t,c,d),n.__i=u,r=null,u!==-1&&(d--,(r=t[u])&&(r.__u|=131072)),r==null||r.__v===null?(u==-1&&i--,typeof n.type!="function"&&(n.__u|=65536)):u!==c&&(u===c+1?i++:u>c?d>f-c?i+=u-c:i--:u<c?u==c-1&&(i=u-c):i=0,u!==o+i&&(n.__u|=65536))):(r=t[c])&&r.key==null&&r.__e&&!(131072&r.__u)&&(r.__e==_.__d&&(_.__d=H(r)),K(r,r,!1),t[c]=null,d--);if(d)for(o=0;o<l;o++)(r=t[o])!=null&&!(131072&r.__u)&&(r.__e==_.__d&&(_.__d=H(r)),K(r,r))}function ge(_,e,t){var o,n;if(typeof _.type=="function"){for(o=_.__k,n=0;o&&n<o.length;n++)o[n]&&(o[n].__=_,e=ge(o[n],e,t));return e}_.__e!=e&&(t.insertBefore(_.__e,e||null),e=_.__e);do e=e&&e.nextSibling;while(e!=null&&e.nodeType===8);return e}function He(_,e,t,o){var n=_.key,r=_.type,c=t-1,u=t+1,f=e[t];if(f===null||f&&n==f.key&&r===f.type&&!(131072&f.__u))return t;if(o>(f!=null&&!(131072&f.__u)?1:0))for(;c>=0||u<e.length;){if(c>=0){if((f=e[c])&&!(131072&f.__u)&&n==f.key&&r===f.type)return c;c--}if(u<e.length){if((f=e[u])&&!(131072&f.__u)&&n==f.key&&r===f.type)return u;u++}}return-1}function ne(_,e,t){e[0]==="-"?_.setProperty(e,t??""):_[e]=t==null?"":typeof t!="number"||Se.test(e)?t:t+"px"}function F(_,e,t,o,n){var r;e:if(e==="style")if(typeof t=="string")_.style.cssText=t;else{if(typeof o=="string"&&(_.style.cssText=o=""),o)for(e in o)t&&e in t||ne(_.style,e,"");if(t)for(e in t)o&&t[e]===o[e]||ne(_.style,e,t[e])}else if(e[0]==="o"&&e[1]==="n")r=e!==(e=e.replace(/(PointerCapture)$|Capture$/i,"$1")),e=e.toLowerCase()in _||e==="onFocusOut"||e==="onFocusIn"?e.toLowerCase().slice(2):e.slice(2),_.l||(_.l={}),_.l[e+r]=t,t?o?t.u=o.u:(t.u=Q,_.addEventListener(e,r?z:j,r)):_.removeEventListener(e,r?z:j,r);else{if(n=="http://www.w3.org/2000/svg")e=e.replace(/xlink(H|:h)/,"h").replace(/sName$/,"s");else if(e!="width"&&e!="height"&&e!="href"&&e!="list"&&e!="form"&&e!="tabIndex"&&e!="download"&&e!="rowSpan"&&e!="colSpan"&&e!="role"&&e in _)try{_[e]=t??"";break e}catch{}typeof t=="function"||(t==null||t===!1&&e[4]!=="-"?_.removeAttribute(e):_.setAttribute(e,t))}}function oe(_){return function(e){if(this.l){var t=this.l[e.type+_];if(e.t==null)e.t=Q++;else if(e.t<t.u)return;return t(v.event?v.event(e):e)}}}function Y(_,e,t,o,n,r,c,u,f,l){var d,i,p,s,g,x,b,h,k,S,N,L,ee,E,V,w=e.type;if(e.constructor!==void 0)return null;128&t.__u&&(f=!!(32&t.__u),r=[u=e.__e=t.__e]),(d=v.__b)&&d(e);e:if(typeof w=="function")try{if(h=e.props,k=(d=w.contextType)&&o[d.__c],S=d?k?k.props.value:d.__:o,t.__c?b=(i=e.__c=t.__c).__=i.__E:("prototype"in w&&w.prototype.render?e.__c=i=new w(h,S):(e.__c=i=new W(h,S),i.constructor=w,i.render=Ce),k&&k.sub(i),i.props=h,i.state||(i.state={}),i.context=S,i.__n=o,p=i.__d=!0,i.__h=[],i._sb=[]),i.__s==null&&(i.__s=i.state),w.getDerivedStateFromProps!=null&&(i.__s==i.state&&(i.__s=$({},i.__s)),$(i.__s,w.getDerivedStateFromProps(h,i.__s))),s=i.props,g=i.state,i.__v=e,p)w.getDerivedStateFromProps==null&&i.componentWillMount!=null&&i.componentWillMount(),i.componentDidMount!=null&&i.__h.push(i.componentDidMount);else{if(w.getDerivedStateFromProps==null&&h!==s&&i.componentWillReceiveProps!=null&&i.componentWillReceiveProps(h,S),!i.__e&&(i.shouldComponentUpdate!=null&&i.shouldComponentUpdate(h,i.__s,S)===!1||e.__v===t.__v)){for(e.__v!==t.__v&&(i.props=h,i.state=i.__s,i.__d=!1),e.__e=t.__e,e.__k=t.__k,e.__k.forEach(function(T){T&&(T.__=e)}),N=0;N<i._sb.length;N++)i.__h.push(i._sb[N]);i._sb=[],i.__h.length&&c.push(i);break e}i.componentWillUpdate!=null&&i.componentWillUpdate(h,i.__s,S),i.componentDidUpdate!=null&&i.__h.push(function(){i.componentDidUpdate(s,g,x)})}if(i.context=S,i.props=h,i.__P=_,i.__e=!1,L=v.__r,ee=0,"prototype"in w&&w.prototype.render){for(i.state=i.__s,i.__d=!1,L&&L(e),d=i.render(i.props,i.state,i.context),E=0;E<i._sb.length;E++)i.__h.push(i._sb[E]);i._sb=[]}else do i.__d=!1,L&&L(e),d=i.render(i.props,i.state,i.context),i.state=i.__s;while(i.__d&&++ee<25);i.state=i.__s,i.getChildContext!=null&&(o=$($({},o),i.getChildContext())),p||i.getSnapshotBeforeUpdate==null||(x=i.getSnapshotBeforeUpdate(s,g)),ye(_,X(V=d!=null&&d.type===B&&d.key==null?d.props.children:d)?V:[V],e,t,o,n,r,c,u,f,l),i.base=e.__e,e.__u&=-161,i.__h.length&&c.push(i),b&&(i.__E=i.__=null)}catch(T){e.__v=null,f||r!=null?(e.__e=u,e.__u|=f?160:32,r[r.indexOf(u)]=null):(e.__e=t.__e,e.__k=t.__k),v.__e(T,e,t)}else r==null&&e.__v===t.__v?(e.__k=t.__k,e.__e=t.__e):e.__e=Le(t.__e,e,t,o,n,r,c,f,l);(d=v.diffed)&&d(e)}function be(_,e,t){e.__d=void 0;for(var o=0;o<t.length;o++)Z(t[o],t[++o],t[++o]);v.__c&&v.__c(e,_),_.some(function(n){try{_=n.__h,n.__h=[],_.some(function(r){r.call(n)})}catch(r){v.__e(r,n.__v)}})}function Le(_,e,t,o,n,r,c,u,f){var l,d,i,p,s,g,x,b=t.props,h=e.props,k=e.type;if(k==="svg"?n="http://www.w3.org/2000/svg":k==="math"?n="http://www.w3.org/1998/Math/MathML":n||(n="http://www.w3.org/1999/xhtml"),r!=null){for(l=0;l<r.length;l++)if((s=r[l])&&"setAttribute"in s==!!k&&(k?s.localName===k:s.nodeType===3)){_=s,r[l]=null;break}}if(_==null){if(k===null)return document.createTextNode(h);_=document.createElementNS(n,k,h.is&&h),r=null,u=!1}if(k===null)b===h||u&&_.data===h||(_.data=h);else{if(r=r&&I.call(_.childNodes),b=t.props||C,!u&&r!=null)for(b={},l=0;l<_.attributes.length;l++)b[(s=_.attributes[l]).name]=s.value;for(l in b)if(s=b[l],l!="children"){if(l=="dangerouslySetInnerHTML")i=s;else if(l!=="key"&&!(l in h)){if(l=="value"&&"defaultValue"in h||l=="checked"&&"defaultChecked"in h)continue;F(_,l,null,s,n)}}for(l in h)s=h[l],l=="children"?p=s:l=="dangerouslySetInnerHTML"?d=s:l=="value"?g=s:l=="checked"?x=s:l==="key"||u&&typeof s!="function"||b[l]===s||F(_,l,s,b[l],n);if(d)u||i&&(d.__html===i.__html||d.__html===_.innerHTML)||(_.innerHTML=d.__html),e.__k=[];else if(i&&(_.innerHTML=""),ye(_,X(p)?p:[p],e,t,o,k==="foreignObject"?"http://www.w3.org/1999/xhtml":n,r,c,r?r[0]:t.__k&&H(t,0),u,f),r!=null)for(l=r.length;l--;)r[l]!=null&&ve(r[l]);u||(l="value",g!==void 0&&(g!==_[l]||k==="progress"&&!g||k==="option"&&g!==b[l])&&F(_,l,g,b[l],n),l="checked",x!==void 0&&x!==_[l]&&F(_,l,x,b[l],n))}return _}function Z(_,e,t){try{typeof _=="function"?_(e):_.current=e}catch(o){v.__e(o,t)}}function K(_,e,t){var o,n;if(v.unmount&&v.unmount(_),(o=_.ref)&&(o.current&&o.current!==_.__e||Z(o,null,e)),(o=_.__c)!=null){if(o.componentWillUnmount)try{o.componentWillUnmount()}catch(r){v.__e(r,e)}o.base=o.__P=null}if(o=_.__k)for(n=0;n<o.length;n++)o[n]&&K(o[n],e,t||typeof _.type!="function");t||_.__e==null||ve(_.__e),_.__c=_.__=_.__e=_.__d=void 0}function Ce(_,e,t){return this.constructor(_,t)}function Ne(_,e,t){var o,n,r,c;v.__&&v.__(_,e),n=(o=typeof t=="function")?null:e.__k,r=[],c=[],Y(e,_=(!o&&t||e).__k=$e(B,null,[_]),n||C,C,e.namespaceURI,!o&&t?[t]:n?null:e.firstChild?I.call(e.childNodes):null,r,!o&&t?t:n?n.__e:e.firstChild,o,c),be(r,_,c)}I=he.slice,v={__e:function(_,e,t,o){for(var n,r,c;e=e.__;)if((n=e.__c)&&!n.__)try{if((r=n.constructor)&&r.getDerivedStateFromError!=null&&(n.setState(r.getDerivedStateFromError(_)),c=n.__d),n.componentDidCatch!=null&&(n.componentDidCatch(_,o||{}),c=n.__d),c)return n.__E=n}catch(u){_=u}throw _}},de=0,W.prototype.setState=function(_,e){var t;t=this.__s!=null&&this.__s!==this.state?this.__s:this.__s=$({},this.state),typeof _=="function"&&(_=_($({},t),this.props)),_&&$(t,_),_!=null&&this.__v&&(e&&this._sb.push(e),te(this))},W.prototype.forceUpdate=function(_){this.__v&&(this.__e=!0,_&&this.__h.push(_),te(this))},W.prototype.render=B,P=[],pe=typeof Promise=="function"?Promise.prototype.then.bind(Promise.resolve()):setTimeout,R=function(_,e){return _.__v.__b-e.__v.__b},M.__r=0,Q=0,j=oe(!1),z=oe(!0);var O,m,q,re,G=0,ke=[],D=[],y=v,ie=y.__b,le=y.__r,ce=y.diffed,ue=y.__c,fe=y.unmount,se=y.__;function we(_,e){y.__h&&y.__h(m,_,G||e),G=0;var t=m.__H||(m.__H={__:[],__h:[]});return _>=t.__.length&&t.__.push({__V:D}),t.__[_]}function Ee(_){return G=1,Te(xe,_)}function Te(_,e,t){var o=we(O++,2);if(o.t=_,!o.__c&&(o.__=[xe(void 0,e),function(u){var f=o.__N?o.__N[0]:o.__[0],l=o.t(f,u);f!==l&&(o.__N=[l,o.__[1]],o.__c.setState({}))}],o.__c=m,!m.u)){var n=function(u,f,l){if(!o.__c.__H)return!0;var d=o.__c.__H.__.filter(function(p){return!!p.__c});if(d.every(function(p){return!p.__N}))return!r||r.call(this,u,f,l);var i=!1;return d.forEach(function(p){if(p.__N){var s=p.__[0];p.__=p.__N,p.__N=void 0,s!==p.__[0]&&(i=!0)}}),!(!i&&o.__c.props===u)&&(!r||r.call(this,u,f,l))};m.u=!0;var r=m.shouldComponentUpdate,c=m.componentWillUpdate;m.componentWillUpdate=function(u,f,l){if(this.__e){var d=r;r=void 0,n(u,f,l),r=d}c&&c.call(this,u,f,l)},m.shouldComponentUpdate=n}return o.__N||o.__}function Fe(_,e){var t=we(O++,3);!y.__s&&De(t.__H,e)&&(t.__=_,t.i=e,m.__H.__h.push(t))}function Ue(){for(var _;_=ke.shift();)if(_.__P&&_.__H)try{_.__H.__h.forEach(A),_.__H.__h.forEach(J),_.__H.__h=[]}catch(e){_.__H.__h=[],y.__e(e,_.__v)}}y.__b=function(_){m=null,ie&&ie(_)},y.__=function(_,e){_&&e.__k&&e.__k.__m&&(_.__m=e.__k.__m),se&&se(_,e)},y.__r=function(_){le&&le(_),O=0;var e=(m=_.__c).__H;e&&(q===m?(e.__h=[],m.__h=[],e.__.forEach(function(t){t.__N&&(t.__=t.__N),t.__V=D,t.__N=t.i=void 0})):(e.__h.forEach(A),e.__h.forEach(J),e.__h=[],O=0)),q=m},y.diffed=function(_){ce&&ce(_);var e=_.__c;e&&e.__H&&(e.__H.__h.length&&(ke.push(e)!==1&&re===y.requestAnimationFrame||((re=y.requestAnimationFrame)||We)(Ue)),e.__H.__.forEach(function(t){t.i&&(t.__H=t.i),t.__V!==D&&(t.__=t.__V),t.i=void 0,t.__V=D})),q=m=null},y.__c=function(_,e){e.some(function(t){try{t.__h.forEach(A),t.__h=t.__h.filter(function(o){return!o.__||J(o)})}catch(o){e.some(function(n){n.__h&&(n.__h=[])}),e=[],y.__e(o,t.__v)}}),ue&&ue(_,e)},y.unmount=function(_){fe&&fe(_);var e,t=_.__c;t&&t.__H&&(t.__H.__.forEach(function(o){try{A(o)}catch(n){e=n}}),t.__H=void 0,e&&y.__e(e,t.__v))};var ae=typeof requestAnimationFrame=="function";function We(_){var e,t=function(){clearTimeout(o),ae&&cancelAnimationFrame(e),setTimeout(_)},o=setTimeout(t,100);ae&&(e=requestAnimationFrame(t))}function A(_){var e=m,t=_.__c;typeof t=="function"&&(_.__c=void 0,t()),m=e}function J(_){var e=m;_.__c=_.__(),m=e}function De(_,e){return!_||_.length!==e.length||e.some(function(t,o){return t!==_[o]})}function xe(_,e){return typeof e=="function"?e(_):e}var Ae=0;function a(_,e,t,o,n,r){e||(e={});var c,u,f=e;if("ref"in f)for(u in f={},e)u=="ref"?c=e[u]:f[u]=e[u];var l={type:_,props:f,key:t,ref:c,__k:null,__:null,__b:0,__e:null,__d:void 0,__c:null,constructor:void 0,__v:--Ae,__i:-1,__u:0,__source:n,__self:r};if(typeof _=="function"&&(c=_.defaultProps))for(u in c)f[u]===void 0&&(f[u]=c[u]);return v.vnode&&v.vnode(l),l}function Me(){const[_,e]=Ee([0,111,222,333,444,555,666,777,888,999,1e3,1111,1222,1333,1444,1555]);async function t(){const r=await(await fetch("/offset")).json();e(r)}Fe(()=>{t()},[]);async function o(n){n.preventDefault();const r=new FormData(n.target);await fetch("/offset",{method:"POST",body:r}),await t()}return a("div",{class:"content",children:a("div",{class:"card-grid",children:[a("form",{action:"/",method:"post",id:"form",children:a("div",{class:"card",children:[a("p",{class:"card-title",children:"Text Alignment"}),a("div",{class:"line",children:[a("div",{class:"inputWithLabel",children:[a("input",{type:"radio",id:"textleft",name:"alignment",autocomplete:"off",value:"left"}),a("label",{for:"textleft",children:"left-aligned"})]}),a("div",{class:"inputWithLabel",children:[a("input",{type:"radio",id:"textcenter",name:"alignment",autocomplete:"off",value:"center"}),a("label",{for:"textcenter",children:"centered"})]}),a("div",{class:"inputWithLabel",children:[a("input",{type:"radio",id:"textright",name:"alignment",autocomplete:"off",value:"right"}),a("label",{for:"textright",children:"right-aligned"})]})]}),a("input",{id:"SpeedSlider",name:"speedslider",hidden:!0,min:"1",max:"100",step:"1",value:100}),a("p",{class:"card-title",children:"What to Show"}),a("div",{class:"line",children:[a("div",{class:"inputWithLabel",children:[a("input",{type:"radio",id:"modetext",name:"devicemode",value:"text"}),a("label",{for:"modetext",children:"Text"})]}),a("div",{class:"inputWithLabel",children:[a("input",{type:"radio",id:"modedate",name:"devicemode",value:"date"}),a("label",{for:"modedate",children:"Date"})]}),a("div",{class:"inputWithLabel",children:[a("input",{type:"radio",id:"modeclock",name:"devicemode",value:"clock"}),a("label",{for:"modeclock",children:"Clock"})]})]}),a("input",{type:"text",id:"text",name:"text",autocomplete:"off",maxlength:16}),a("input",{type:"submit",value:"Submit"})]})}),a("div",{class:"card",children:[a("p",{class:"card-title",children:"Offsets"}),a("div",{class:"line",children:_.map((n,r)=>a("form",{action:"/offset",method:"post",id:"offsetForm",onSubmit:o,children:a("div",{class:"offsetLine",children:[a("div",{class:"inputWithLabel",children:[a("label",{class:"label",for:"offset",children:["Unit ",r]}),a("input",{type:"number",name:"offset",value:n,min:0,max:9999})]},r),a("input",{type:"hidden",name:"unit",value:r}),a("input",{type:"submit",value:"Submit",id:"offsetSubmitButton"})]})}))})]})]})})}Ne(a(Me,{}),document.getElementById("app"));